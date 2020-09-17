/* -*- c++ -*- */
/*
 * Copyright 2020 Paul Boven <boven@jive.eu>.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "VDIF_packetize_impl.h"

namespace gr {
  namespace vdif {

    VDIF_packetize::sptr
    VDIF_packetize::make(unsigned int frame_length, unsigned int start_time, bool VTP, char * station_code)
    {
      return gnuradio::get_initial_sptr
        (new VDIF_packetize_impl(frame_length, start_time, VTP, station_code));
    }


    /*
     * The private constructor
     */
    VDIF_packetize_impl::VDIF_packetize_impl(unsigned int frame_length, unsigned int start_time, bool VTP, char * station_code)
      : gr::block("VDIF_packetize",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char))),
              d_frame_length(frame_length), d_start_time(start_time)
    {
        struct tm tm_epoch;
        struct timespec ts_epoch;
        unsigned int hye; /* Half year epoch */
        time_t epoch;

        /* Advise GRS of the output block size */
        set_output_multiple(frame_length + 32);

        /* Construct/clear the VDIF header */
        bzero(&vh, sizeof(struct vdif_header));

        /* Calculate the VDIF epoch and the Half Year Epoch */
        ts_epoch.tv_sec = start_time;
        ts_epoch.tv_nsec = 0;
        gmtime_r(&ts_epoch.tv_sec, &tm_epoch);
        hye = 2*(tm_epoch.tm_year - 100);
        if(tm_epoch.tm_mon > 5) hye++;
        bzero(&tm_epoch, sizeof(tm_epoch));
        tm_epoch.tm_year = 100 + hye/2;
        tm_epoch.tm_mon = 6 * (hye%2);
        tm_epoch.tm_mday = 1;
        epoch = timegm(&tm_epoch);

        /* Fill in the actual VDIF header */
        vh.ref_epoch = hye;
        vh.frame_length = (frame_length + 32)/8;
        vh.bits_sample = 1;
        vh.station_id = 256 * station_code[0] + station_code[1];
        vh.seconds = (time_t)start_time - epoch;
    }

    /*
     * Our virtual destructor.
     */
    VDIF_packetize_impl::~VDIF_packetize_impl()
    {
    }

    void
    VDIF_packetize_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        ninput_items_required[0] = noutput_items/(d_frame_length+32)*d_frame_length*4;
    }

    int
    VDIF_packetize_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      char *out = (char *) output_items[0];

      // Do <+signal processing+>

        unsigned int frame = 0;
        while(frame < noutput_items/(d_frame_length+32))
        {
            memcpy(out, &vh, 32);
            out += 32;
            for (int i = 0; i < d_frame_length; i++)
            {
                char tmp = 0;
                for (int j = 0; j < 4; j++)
                    tmp += (*in++ & 0x03) << j*2;
                *out++ = tmp;
            }
            frame++;
            vh.frame_count++;
            if(vh.frame_count >= 8000)
            {
                vh.frame_count = 0;
                vh.seconds++;
            }
        }

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace vdif */
} /* namespace gr */

