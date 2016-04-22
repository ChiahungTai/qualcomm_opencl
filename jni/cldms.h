/*
                           _    _ _       
                 __ _  ___| | _| (_)_ __  
                / _` |/ __| |/ / | | '_ \
               | (_| | (__|   <| | | | | |
                \__,_|\___|_|\_\_|_|_| |_|
*/
#ifndef _CLDMS_H
#define _CLDMS_H

#include <map>
#include <fstream>
#include <clyuv2rgb.h>
#include <kern_search.h>
#include <clposition.h>
#include <algorithm>

class ClDMS : public ClVideo {
private:
protected:
	ClFrame tmp_frame;
	ClFrame last_img;
	ClOpConvert m_yuv2rgb;
	ClOpSearch m_finditem;
	ClPosition m_postion;
	std::mutex m_ulock;
public:
	ClDMS() {
		tmp_frame.open(m_width, m_height, 4);
		last_img.open(m_width, m_height, 4);
		last_img.fill_color(128, 128, 128, 4);
	};
	~ClDMS() {
		tmp_frame.close();
		last_img.close();
	};
	void process_image(ClFrame &in_frame) {
		PERF_START("image_processing");
		klock lock(m_ulock); // I forgot why i put this here

#ifdef _DEBUG
		if(os.is_set())
			return;
#endif //_DEBUG

		// image correction
		in_frame.set_origin(0, 0, 0);
		in_frame.set_region(m_width, m_height, 1);

		//ocl used to convert yuv2rgb
		m_yuv2rgb.proc(in_frame, rgb_frame, m_thekey.m_mx);
		//copy_yuv2rgb(in_frame, rgb_frame); //TODO: too slow
		//copy_yuv2rgb2(in_frame, rgb_frame); //TODO: too slow

		rgb_frame.set_origin(0, 0, 0);
		rgb_frame.set_region(m_width, m_height, 1);
		process_frame(rgb_frame, tmp_frame);

		PERF_END("image_processing");
	};
	void process_frame(ClFrame &in_frame, ClFrame &out_frame) {
		PERF_START("process_frame");

		if(m_crop) {
			in_frame.set_origin(m_width/2, m_height/2, 0);
			in_frame.set_region(m_width/3, m_height/3, 1);
			out_frame.set_origin(m_width/2, m_height/2, 0);
			out_frame.set_region(m_width/3, m_height/3, 1);
#ifndef _WITH_FRAMECPY
			//in_frame.vflip(); // no need to flip for frame memcpy
#endif //_WITH_FRAMECPY

			set_background_image(bg_img);
		}

		dms_frame(in_frame, out_frame);

		if(m_target.is_search()) {
			if(m_finditem.proc(in_frame, m_postion) == true) {
				m_target.set(m_postion);
				out_frame.framecopy(in_frame);
			}
		}

		display_frame(out_frame);
		PERF_END("process_frame");
	};
	virtual void dms_frame(ClFrame &in_frame, ClFrame &out_frame) {
	};
	void display_frame(ClFrame &frame) {
		if(m_crop) {
			PERF_START("display_image_crop");
			display_image_ocl_crop(frame);
			PERF_END("display_image_crop");
		} else {
			PERF_START("display_image");
			display_image(frame);
			PERF_END("display_image");
		}
	};
	char* cmd_option(char **begin, char **end, const std::string &option, const std::string &def) {
		char ** itr = std::find(begin, end, option);
		if (itr != end && ++itr != end) {
			return strdup(*itr);
		}
		return strdup(def.c_str());
	};
	bool cmd_exists(char** begin, char** end, const std::string& option) {
		return std::find(begin, end, option) != end;
	};
	/*
	unsigned char *img_pos(unsigned char *start, int x, int y, int bpp, int width) {
		return start + (y * (width * bpp)) + (x * bpp);
	}
	unsigned char * copy_yuv2rgb2(ClFrame &in_frame, ClFrame &out_frame) {
		PERF_START("process_yuv");
		unsigned char *dest;
		unsigned char *src;
		for(int y = 0; y < in_frame.height(); y++) {
			for(int x = 0; x < in_frame.width()/2; x++) { //<<<== 8/4=2 
				src = (unsigned char *)img_pos(in_frame.get(), x, y, 4, in_frame.width()/2);
				dest = (unsigned char *)img_pos(out_frame.get(), x, y, 8, out_frame.width()/2);

				yuv2rgb(dest, 0, src[0], 128, 16, src[1], src[3]);
				yuv2rgb(dest, 4, src[2], 128, 16, src[1], src[3]);
			}
		}
		PERF_END("process_yuv");
		//os.set();
	}
	unsigned char * copy_yuv2rgb(ClFrame &in_frame, ClFrame &out_frame) {
		PERF_START("process_yuv");
		unsigned char *tmp_img = out_frame.get();
		char *current = (char *)in_frame.get();
		int x, y;
		y = 0;
		while(y < m_height) {
			x = 0;
			while(x < m_width) {

				//char Y = current[0];
				//char U = current[1];
				//char Y2 = current[2];
				//char V = current[3];

				yuv2rgb(tmp_img, 0, current[0], 128, 16, current[1], current[3]);
				yuv2rgb(tmp_img, 4, current[2], 128, 16, current[1], current[3]);

				tmp_img = tmp_img + 8;
				current = current + 4;
				x = x + 2;
			}
			current = ((char *)in_frame.get()) + y * m_width * 2;
			y++;
		}
		PERF_END("process_yuv");
	}
	*/

};

// cldms
#endif //_CLDMS_H
