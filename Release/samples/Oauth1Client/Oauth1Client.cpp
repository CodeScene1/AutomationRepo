/***
* ==++==
*
* Copyright (c) Microsoft Corporation. All rights reserved. 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* ==--==
* =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
*
* Oauth1Client.cpp : Defines the entry point for the console application
*
* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
****/

#include "stdafx.h"


using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;


//
// LinkedIn tokens. Fill the following based on information here:
// https://developer.linkedin.com/documents/quick-start-guide
//
static const string_t s_linkedin_key(U(""));
static const string_t s_linkedin_secret(U(""));
static const string_t s_linkedin_user_token(U(""));
static const string_t s_linkedin_user_token_secret(U(""));


static void linkedin_client()
{
    http_client_config config;
    config.set_oauth1(oauth1_config(s_linkedin_key, s_linkedin_secret,
            s_linkedin_user_token, s_linkedin_user_token_secret,
            oauth1_methods::hmac_sha1));
    http_client c(U("http://api.linkedin.com/"), config);

    ucout << "Requesting user information:" << std::endl;
    auto user_json = c.request(methods::GET, U("v1/people/~?format=json")).get().extract_json().get();
    ucout << "Got following JSON:" << std::endl;
    ucout << user_json.serialize().c_str() << std::endl;
}

static int has_key(string_t client_name, string_t key)
{
    if (key.empty())
    {
        ucout << "Skipped " << client_name.c_str() << " client. Please supply tokens for the client." << std::endl;
        return 0;
    }
    else
    {
        ucout << "Running " << client_name.c_str() << " client." << std::endl;
        return 1;
    }
}

#ifdef _MS_WINDOWS
int wmain(int argc, wchar_t *argv[])
#else
int main(int argc, char *argv[])
#endif
{
    ucout << "Running oauth1 sample..." << std::endl;
    if (has_key(U("LinkedIn"), s_linkedin_key))
    {
        linkedin_client();
    }
    ucout << "Done." << std::endl;
    return 0;
}

