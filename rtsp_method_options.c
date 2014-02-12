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
 * @brief Contains OPTIONS method and reply handlers
 */

#include "rtsp.h"

/**
 * RTSP OPTIONS method handler
 * @param rtsp the buffer for which to handle the method
 * @param req The client request for the method
 */
void RTSP_options(RTSP_Client *rtsp, RFC822_Request *req)
{
    RFC822_Response *response = rfc822_response_new(req, RTSP_Ok);

    rfc822_headers_set(response->headers,
                       RTSP_Header_Public,
                       g_strdup("OPTIONS,DESCRIBE,SETUP,PLAY,PAUSE,TEARDOWN"));

    rfc822_response_send(rtsp, response);
}
