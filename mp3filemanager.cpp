#include "mp3filemanager.h"
#include "song.h"
#include <vector>
#include <fstream>
#include <string>
#include <filesystem>
void mp3FileManager::saveAll(mp3Manager& m){
    ofstream file("cache");
    file<<"</cache>\n";
    for(int i = 0;i<m.getFilepathContainer()->size();i++){
        file<<(*(m.getFilepathContainer()))[i]<<'\n';
    }
    file.close();
    file.open("cachesongs");
    file<<"</cachesongs>";
    file<<'\n';
    for(int i = 0;i<m.getDatabase()->size();i++){
        file<<(*(m.getDatabase()))[i].serialize();
    }
}
void mp3FileManager::loadFilepaths(mp3Manager& m){
    ifstream file("cache");
    vector<string>* output = m.getFilepathContainer();
    output->clear();
    string check;
    getline(file,check);
    string input;
    if(check == "</cache>"){
        getline(file,input);
        while(input!=""){
            output->push_back(input);
            getline(file,input);
        }
    }
    file.close();
}
vector<song> mp3FileManager::getSongs(vector<string> input){
    namespace fs = std::filesystem;
    vector<song> output;
    for(int i = 0;i<input.size();i++){
       if(fs::exists(input[i])){
        for(auto& p: fs::recursive_directory_iterator(input[i])){
            string path = p.path();
            if((!p.is_directory())&&(path.find(".mp3") == path.size()-4)){
                song temp;
                temp.updateSongClass(path);
                output.push_back(temp);
            }
        }
        }
    }
    return output;
}
void mp3FileManager::loadSongs(mp3Manager &m){
    ifstream file("cachesongs");
    vector<song>* output = m.getDatabase();
    output->clear();
    string check;
    getline(file,check);
    if(check == "</cachesongs>"){
        while(!file.eof()){
            song temp;
            temp.deserialize(file);
            output->push_back(temp);
        }
    }
    output->pop_back();
    file.close();
}
