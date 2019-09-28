#include "tp.h"
#include "runtime/types.cpp"

// TODO option in Makefile USE_PYTHON
#define USE_PYTHON 1
extern "C" int PyRun_SimpleString(const char* script);

void tp_save(TP, const char * fname, tp_obj v) {
	FILE *f;
	f = fopen(fname,"wb");
	if (!f) {
		tp_raise(, tp_string_atom(tp, "(tp_save) IOError: ?"));
	}
	fwrite(tp_string_getptr(v), tp_string_len(v), 1, f);
	fclose(f);
}

tp_obj tp_load(TP, const char * fname) {
	FILE *f;
	long l;
	tp_obj r;
	char *s;
	struct stat stbuf;
	stat(fname, &stbuf);
	l = stbuf.st_size;
	f = fopen(fname,"rb");
	if (!f) {
		tp_raise(tp_None,tp_string_atom(tp, "(tp_load) IOError: ?"));
	}
	r = tp_string_t(tp, l);
	s = tp_string_getptr(r);
	size_t num_elements_read = fread(s, 1, l, f);
/*    if (rr !=l) { printf("hmmn: %d %d\n",rr,(int)l); }*/
	if (num_elements_read !=l) {
		printf(" - EOF or file read error\n");
	}

	fclose(f);
	return r;
}


tp_obj tpy_exists(TP) {
	char * fname = tp_cstr(tp, TP_STR());
	struct stat stbuf;
	tp_obj r = tp_number(!stat(fname, &stbuf));
	tp_free(tp, fname);
	return r;
}

tp_obj tpy_load(TP) {
	char * fname = tp_cstr(tp, TP_STR());
	tp_obj r = tp_load(tp, fname);
	tp_free(tp, fname);
	return r;
}

tp_obj tpy_save(TP) {
	char * fname = tp_cstr(tp, TP_STR());
	tp_obj v = TP_OBJ();
	tp_save(tp, fname, v);
	tp_free(tp, fname);
	return tp_None;
}


tp_obj tpy_mtime(TP) {
	char * fname = tp_cstr(tp, TP_STR());
	struct stat stbuf;
	tp_obj r;
	if (!stat(fname, &stbuf)) {
		tp_free(tp, fname);
		r = tp_number(stbuf.st_mtime);
		return r;
	} else {
		tp_free(tp, fname);
		tp_raise(tp_None, tp_string_atom(tp, "(tp_mtime) IOError: ?"));
	}
}


/* Function: tp_system
 *
 * The system builtin. A grave security flaw. If your version of tinypy
 * enables this, you better remove it before deploying your app :P
 */
tp_obj tpy_system(TP) {
	char * s = tp_cstr(tp, TP_STR());
	int r = system(s);
	tp_free(tp, s);
	return tp_number(r);
}

void tp_module_os_init(TP) {
	tp_obj os = tp_import(tp, tp_string_atom(tp, "os"), tp_None, tp_string_atom(tp, "<builtin>"));
	tp_set(tp, os, tp_string_atom(tp, "exists"), tp_function(tp, tpy_exists));
	tp_set(tp, os, tp_string_atom(tp, "read"), tp_function(tp, tpy_load));
	tp_set(tp, os, tp_string_atom(tp, "load"), tp_function(tp, tpy_load));
	tp_set(tp, os, tp_string_atom(tp, "system"), tp_function(tp, tpy_system));
	tp_set(tp, os, tp_string_atom(tp, "mtime"), tp_function(tp, tpy_mtime));
	tp_set(tp, os, tp_string_atom(tp, "save"), tp_function(tp, tpy_save));
}

// CPython integration //
#ifdef USE_PYTHON
	tp_obj tpy_cpython_run(TP) {
		char * s = tp_cstr(tp, TP_STR());
		int r = PyRun_SimpleString(s);  // returns -1 on failure
		tp_free(tp, s);
		return tp_number(r);
	}
	/* TODO
	tp_obj tpy_cpython_eval(TP) {
		char * s = tp_cstr(tp, TP_STR());
		PyObject *r = PyRun_String(s);  // returns NULL on failure
		tp_free(tp, s);
		return tp_pyobject(r);
	}
	*/

#endif

void tp_module_cpython_init(TP) {
	tp_obj py = tp_import(tp, tp_string_atom(tp, "python"), tp_None, tp_string_atom(tp, "<builtin>"));
	tp_set(tp, py, tp_string_atom(tp, "run"), tp_function(tp, tpy_cpython_run));
}


void tp_module_corelib_init(TP) {
	#ifdef DEBUG
		std::cout << "runtime.cpp:tp_module_corelib_init" << std::endl;
	#endif
	//tp_import_from_buffer(tp, 0, "tinypy.runtime.types", _tp_types_tpc,  sizeof(_tp_types_tpc));
	tp_import_from_buffer(tp, "tinypy.runtime.types", _tp_types_tpc,  sizeof(_tp_types_tpc));
	tp_module_os_init(tp);
	#ifdef USE_PYTHON
		tp_module_cpython_init(tp);
	#endif
}
