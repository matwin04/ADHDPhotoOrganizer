//
// Created by mwiner on 12/13/24.
//

#include "organizer.h"
#include <iostream>
#include <filesystem>
#include <exiv2/exiv2.hpp>
namespace fs = std::filesystem;

organizer::organizer(const std::string& source, const std::string& target)
        : sourceDir(source), targetDir(target), filesOrganized(0) {}

std::string organizer::getPhotoDate(const std::string& filePath, bool& success) {
    success = false;
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(filePath);
    if (!image.get()){
        std::cerr << "ERR 1 - Failed to open image\n";
        return "unknown";
    }
    image->readMetadata();
    Exiv2::ExifData& exifData = image->exifData();
    if (exifData["Exif.Photo.DateTimeOriginal"].count()>0){
        success = true;
        std::string dateTime = exifData["Exif.Photo.DateTimeOriginal"].toString();
        return dateTime.substr(0,10);
    }
    std::cerr << "ERR 2 - No Date Metadata for file: " << filePath << std::endl;
    return "Unknown";
}

//create Dir
void organizer::createDir(const std::string& path) {
    if (!fs::exists(path)){
        if (!fs::create_directory(path)){
            std::cerr << "ERR 3 - Failed to create : " << path << std::endl;
        }
    }
}

void organizer::moveFile(const std::string &filePath, const std::string &date,bool success) {
    std::string dateFolder = targetDir + "/" +date;
    createDir(dateFolder);
    std::string targetPath = dateFolder + "/" + fs::path(filePath).filename().string();
    try{
        fs::rename(filePath,targetPath);
        success = true;
        filesOrganized++;
        std::cout << "Moved" << filePath << " to " << targetPath << std::endl;
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "ERR 4 - Error moving file: " << filePath << " -> " << targetPath << " (" << e.what() << ")" << std::endl;
        success = false;
    }
}
void organizer::organizePhotos() {
    createDir(targetDir);

    for (const auto& entry : fs::directory_iterator(sourceDir)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();
            bool dateSuccess = false;
            std::string date = getPhotoDate(filePath, dateSuccess);

            if (dateSuccess) {
                bool moveSuccess = false;
                moveFile(filePath, date, moveSuccess);
                std::cout << "Moved file: " << filePath << std::endl;
            }
        }
    }
}

// Get the number of organized files
int organizer::getFilesOrganized() const {
    return filesOrganized;
}

