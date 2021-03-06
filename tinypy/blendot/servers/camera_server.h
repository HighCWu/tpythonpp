/*************************************************************************/
/*                       This file is part of:                           */
/*                           BLENDOT ENGINE                              */
/*                      https://blendot.org                              */
/*************************************************************************/
/* Copyright (c) 2007-2019 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2019 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef CAMERA_SERVER_H
#define CAMERA_SERVER_H

#include "blendot_object.gen.h"

#ifdef BLENDOT
	#include "thread_safe.h"
#else
	#define _THREAD_SAFE_CLASS_
	#define _THREAD_SAFE_METHOD_

#endif

#include "reference.h"
#include "rid.h"
#include "variant.h"

/**
	@author Bastiaan Olij <mux213@gmail.com>

	The camera server is a singleton object that gives access to the various
	camera feeds that can be used as the background for our environment.
**/

class CameraFeed;

class CameraServer : public Object {
	GDCLASS(CameraServer, Object);
	_THREAD_SAFE_CLASS_

public:
	enum FeedImage {
		FEED_RGBA_IMAGE = 0,
		FEED_YCBCR_IMAGE = 0,
		FEED_Y_IMAGE = 0,
		FEED_CBCR_IMAGE = 1,
		FEED_IMAGES = 2
	};

private:
protected:
	Vector<Ref<CameraFeed> > feeds;

	static CameraServer *singleton;

	static void _bind_methods();

public:
	static CameraServer *get_singleton();

	// Right now we identify our feed by it's ID when it's used in the background.
	// May see if we can change this to purely relying on CameraFeed objects or by name.
	int get_free_id();
	int get_feed_index(int p_id);
	Ref<CameraFeed> get_feed_by_id(int p_id);

	// add and remove feeds
	void add_feed(const Ref<CameraFeed> &p_feed);
	void remove_feed(const Ref<CameraFeed> &p_feed);

	// get our feeds
	Ref<CameraFeed> get_feed(int p_idx);
	int get_feed_count();
	Array get_feeds();

	RID feed_texture(int p_id, FeedImage p_texture);

	CameraServer();
	~CameraServer();
};

VARIANT_ENUM_CAST(CameraServer::FeedImage);

#endif /* CAMERA_SERVER_H */
