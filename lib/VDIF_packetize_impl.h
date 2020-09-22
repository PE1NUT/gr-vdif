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

#ifndef INCLUDED_VDIF_VDIF_PACKETIZE_IMPL_H
#define INCLUDED_VDIF_VDIF_PACKETIZE_IMPL_H

#include <vdif/VDIF_packetize.h>

namespace gr {
  namespace vdif {

    class VDIF_packetize_impl : public VDIF_packetize
    {
     unsigned int d_frame_length;
     unsigned int d_start_time;
     unsigned int d_streams;
     private:
         time_t epoch;
     uint64_t packet_count;
    // VDIF header as a struct
     struct vdif_header {
        uint32_t seconds:30;
        uint32_t legacy:1;
        uint32_t invalid:1;

        uint32_t frame_count:24;
        uint32_t ref_epoch:6;
        uint32_t ua:2;

        uint32_t frame_length:24;
        uint32_t log_chans:5;
        uint32_t version:3;

        uint32_t station_id:16;
        uint32_t thread_id:10;
        uint32_t bits_sample:5;
        uint32_t cplx:1;

        uint32_t EDVA:24;
        uint32_t EDV:8;
        uint32_t EDVB;
        uint32_t EDVC;
        uint32_t EDVD; } vh;

     public:
      VDIF_packetize_impl(unsigned int frame_length, unsigned int start_time, bool VTP, char * station_code, unsigned int streams);
      ~VDIF_packetize_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);

    };

  } // namespace vdif
} // namespace gr

#endif /* INCLUDED_VDIF_VDIF_PACKETIZE_IMPL_H */

