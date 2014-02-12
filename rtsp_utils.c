#include "rtsp.h"
#include <netdb.h>
#include "uri.h"

/**
 * @brief Allocate and initialise a new RTSP session object
 *
 * @param rtsp The RTSP client for which to allocate the session
 *
 * @return A pointer to a newly allocated RTSP session object
 *
 * @see rtsp_session_free();
 */
RTSP_session *rtsp_session_new(RTSP_Client *rtsp)
{
    RTSP_session *new = rtsp->session = g_slice_new0(RTSP_session);

    new->session_id = g_strdup_printf("%08x%08x",
                                      g_random_int(),
                                      g_random_int());
    new->play_requests = g_queue_new();

    return new;
}

void rtsp_session_free(RTSP_session *session)
{

}

/**
 * RTSP Header and request parsing and validation functions
 * @defgroup rtsp_validation Requests parsing and validation
 * @ingroup rtsp_utils
 *
 * @{
 */

/**
 * @brief Checks if the path required by the connection is inside the avroot.
 *
 * @param url The URI structure to validate.
 *
 * @retval true The URL does not contian any forbidden sequence.
 * @retval false The URL contains forbidden sequences that might have malicious
 *         intent.
 *
 * @todo This function should be moved to netembryo.
 * @todo This function does not check properly for paths.
 */
static gboolean check_forbidden_path(URI *uri)
{
    if ( strstr(uri->path, "../") || strstr(uri->path, "./") )
        return false;

    return true;
}


/**
 * @brief Takes care of extracting and validating an URL from the a request
 *        structure.
 *
 * @param req The request structure from where to extract the URL
 *
 * @retval true The URL is valid and allowed
 * @retval false The URL is not not valid or forbidden
 *
 * This function already takes care of sending a 400 "Bad Request" response for
 * invalid URLs or a 403 "Forbidden" reply for paths that try to exit the
 * accessible sandbox.
 *
 * @retval true The URL was properly found and extracted
 * @retval false An error was found, and a reply was already sent.
 */
gboolean rfc822_request_check_url(RTSP_Client *client, RFC822_Request *req)
{
    if(req== NULL)
        xlog(LOG_ERR, "rtsp request is null.");

    if ( req->uri == NULL ) {
        rtsp_quick_response(client, req, RTSP_BadRequest);
        xlog(LOG_ERR, "rtsp request uri is null.");
        return false;
    }

    if ( !check_forbidden_path(req->uri) ) {
        rtsp_quick_response(client, req, RTSP_Forbidden);
        return false;
    }

    return true;
}

