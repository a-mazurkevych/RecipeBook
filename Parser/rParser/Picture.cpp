#include "Picture.h"

Picture::Picture() {
}

Picture::Picture(const std::string& addr)
: m_url(addr) {
}

static std::size_t WriteData(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    std::size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void Picture::Save(const std::string& path) {
    try {
        FILE* picture = fopen(path.c_str(), "wb");
        if (!picture) {
            std::cout << "I can't open " + path + " for writing.." << std::endl;
            return;
        }
        CURL* curl = curl_easy_init();
        if (!curl) {
            std::cout << "I can't init curl.." << std::endl;
            return;
        }
        if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_URL, m_url.c_str()))
            std::cout << "I can't set url: " + m_url + ".." << std::endl;
        if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WriteData))
            std::cout << "I can't set write function.." << std::endl;
        if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_WRITEDATA, picture))
            std::cout << "I can't set write data.." << std::endl;
        if (CURLE_OK != curl_easy_perform(curl))
            std::cout << "I can't perform curl.." << std::endl;
        curl_easy_cleanup(curl);
        fclose(picture);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
