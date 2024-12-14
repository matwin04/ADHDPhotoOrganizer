//
// Created by mwiner on 12/13/24.
//

#ifndef ADHDPHOTOORGANIZER_ORGANIZER_H
#define ADHDPHOTOORGANIZER_ORGANIZER_H

#include <string>
class organizer {
private:
    std::string sourceDir;
    std::string targetDir;
    int filesOrganized;

    //Date Extractor
    std::string getPhotoDate(const std::string &filePath, bool &success);
    void moveFile(const std::string &filePath, const std::string &date, bool success);
    void createDir(const std::string &path);
public:
    organizer(const std::string &source, const std::string &target);
    void organizePhotos();
    int getFilesOrganized() const;


};


#endif //ADHDPHOTOORGANIZER_ORGANIZER_H
