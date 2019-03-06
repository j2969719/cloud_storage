/*
Wfx plugin for working with cloud storage services

Copyright (C) 2019 Ivanenko Danil (ivanenko.danil@gmail.com)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
        License as published by the Free Software Foundation; either
        version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
        Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
        Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
*/

#ifndef CLOUD_STORAGE_YANDEX_REST_CLIENT_H
#define CLOUD_STORAGE_YANDEX_REST_CLIENT_H

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "service_client.h"
#include "httplib.h"
#include "../library.h"

class YandexRestClient: public ServiceClient {
public:
    YandexRestClient();
    ~YandexRestClient();

    std::string get_auth_page_url();

    //std::string get_oauth_token();

    void set_oauth_token(const char *token);

    json get_disk_info() { json j; return j;}

    pResources get_resources(std::string path, BOOL isTrash);

    void makeFolder(std::string utf8Path);

    void removeResource(std::string utf8Path);

    void downloadFile(std::string path, std::ofstream &ofstream);

    void uploadFile(std::string path, std::ifstream &ifstream, BOOL overwrite);

    void move(std::string from, std::string to, BOOL overwrite);

    void copy(std::string from, std::string to, BOOL overwrite);

    void saveFromUrl(std::string urlFrom, std::string pathTo);

    // remove all files from trash
    void cleanTrash();

    // remove one file or folder from trash
    void deleteFromTrash(std::string utf8Path);

private:
    const char* token;
    httplib::SSLClient* http_client;
    httplib::Headers headers;

    void throw_response_error(httplib::Response* resp);
    void wait_success_operation(std::string &body);
    void _do_download(std::string url, std::ofstream &ofstream);
    pResources prepare_folder_result(json json, BOOL isRoot);

};

#endif //CLOUD_STORAGE_YANDEX_REST_CLIENT_H
