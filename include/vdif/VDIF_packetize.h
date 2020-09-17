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

#ifndef INCLUDED_VDIF_VDIF_PACKETIZE_H
#define INCLUDED_VDIF_VDIF_PACKETIZE_H

#include <vdif/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace vdif {

    /*!
     * \brief <+description of block+>
     * \ingroup vdif
     *
     */
    class VDIF_API VDIF_packetize : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<VDIF_packetize> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of vdif::VDIF_packetize.
       *
       * To avoid accidental use of raw pointers, vdif::VDIF_packetize's
       * constructor is in a private implementation
       * class. vdif::VDIF_packetize::make is the public interface for
       * creating new instances.
       */
      static sptr make(unsigned int frame_length, unsigned int start_time, bool VTP, char * station_code);
    };

  } // namespace vdif
} // namespace gr

#endif /* INCLUDED_VDIF_VDIF_PACKETIZE_H */

