from tinypy.compiler import py2bc
from tinypy.compiler.boot import *
from tinypy.compiler import disasm
import os

def do_shorts(opts, optstring, shortopts, args):
	while optstring != '':
		opt, optstring = optstring[0], optstring[1:]
		if short_has_arg(opt, shortopts):
			if optstring == '':
				if not args:
					raise Exception('option -%s requires argument' % opt)
				optstring, args = args[0], args[1:]
			optarg, optstring = optstring, ''
		else:
			optarg = ''
		opts.append(('-' + opt, optarg))
	return opts, args

def short_has_arg(opt, shortopts):
	for i in range(len(shortopts)):
		if opt == shortopts[i] != ':':
			return shortopts.startswith(':', i+1)

	raise Exception('option -%s not recognized' % opt)

def getopt(args, shortopts):
	opts = []
	while args and args[0].startswith('-') and args[0] != '-':
		if args[0].startswith('--'):
			args = args[1:]
			continue
		if args[0] == '--':
			args = args[1:]
			break
		opts, args = do_shorts(opts, args[0][1:], shortopts, args[1:])

	return opts, args

def basename(s, stripdir=True):
	if stripdir:
		for j in range(len(s) - 1, -1, -1):
			if j == -1: break
			if s[j] == '/': break
	else:
		j = -1
	for i in range(len(s) - 1, 0, -1):
		if s[i] == '.': break
	return s[j+1:i]

def main(args=None):
	if args is None: args = ARGV
	posargs = []
	options = {}
	save_as_header = None
	do_debug = False
	for arg in args:
		if arg.startswith('--gen-header='):
			save_as_header = arg.split('=')[-1]
		elif arg == '--debug':
			do_debug = True

	opts, args = getopt(args[1:], 'cn:o:d')
	opts = dict(opts)
	if len(args) == 1:
		src = args[0]
		if '-o' in opts:
			dest = opts['-o']
		else:
			if '-c' in opts:
				dest = basename(args[0], False) + '.c'
			else:
				dest = basename(args[0], False) + '.tpc'
	else:
		print('Usage tinypyc [-c] [-n variable] [-o output_file_name] src.py')
		return 

	s = read(src)
	data = py2bc.compile(s, src)
	if '-d' in opts:
		out = disasm.disassemble(data)
	elif '-c' in opts:
		out = []
		cols = 16
		name = opts.get('-n', '_tp_' + basename(src) + '_tpc')
		out.append("""static unsigned char %s[] = {""" % name)
		for n in range(0, len(data), cols):
			out.append(",".join(["0x%02x" % ord(v) for v in data[n:n+cols]]) + ',')

		out.append("""};""")
		out = '\n'.join(out)
	elif save_as_header:
		out = []
		if do_debug:
			out.append('/*')
			out.append(s)
			out.append('*/')
		cols = 16
		name = save_as_header.replace('.', '_')
		out.append("""static unsigned char __%s__[] = {""" % name)
		for n in range(0, len(data), cols):
			out.append(",".join(["0x%02x" % ord(v) for v in data[n:n+cols]]) + ',')

		out.append("""};""")
		out = '\n'.join(out)
		pth,fname = os.path.split( args[-1] )
		dest = os.path.join(pth, save_as_header)
		print('saving header to: ' + dest)
	else:
		out = data

	if dest == '-':
		print(out)
	else:
		save(dest, out)

if __name__ == '__main__':
	main()
