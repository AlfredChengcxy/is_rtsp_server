/* *
 * This file is part of Feng
 *
 * Copyright (C) 2009 by LScube team <team@lscube.org>
 * See AUTHORS for more details
 *
 * feng is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * feng is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with feng; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * */

/** @file
 * @brief Contains TEARDOWN method and reply handlers
 */

#include "rtsp.h"

/**
 * RTSP TEARDOWN method handler
 * @param rtsp the buffer for which to handle the method
 * @param req The client request for the method
 * @todo trigger the release of rtp resources here
 */
void RTSP_teardown(RTSP_Client *rtsp, RFC822_Request *req)
{
    if ( !rfc822_request_check_url(rtsp, req) )
        return;
    rtsp_session_free(rtsp->session);
    rtsp->session = NULL;

    rtsp_quick_response(rtsp, req, RTSP_Ok);
}
