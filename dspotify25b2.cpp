// You can edit anything you want in this file.
// However you need to implement all public DSpotify function, as provided below as a template

#include "dspotify25b2.h"
#include <ostream>
#include <iostream>
#include "dspotify25b2.h"
#include "wet2util.h"
#include <memory>

DSpotify::DSpotify(){

}

DSpotify::~DSpotify(){

}

StatusType DSpotify::addGenre(int genreId){
    try {
        if(genreId<=0) return StatusType::INVALID_INPUT;
        genres.insert(genreId);
    }
    catch (const std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
    catch (const MyFailure&){
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType DSpotify::addSong(int songId, int genreId){

    try {
        if((songId<=0) || (genreId<=0)) return StatusType::INVALID_INPUT;
        Node* temp1 = genres.find(genreId);
        Node* temp2 = songs.insert(songId);
        if(temp1->getParent() == nullptr) {
            temp1->setParent(temp2);
            temp2->setParent(temp1);
        }
        else{
            temp2->setParent(temp1->getParent());
        }
        temp1->updateGenreChange();
    }
    catch (const std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
    catch (const MyFailure&){
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType DSpotify::mergeGenres(int genreId1, int genreId2, int genreId3){
    try {
        if((genreId1<=0) || (genreId2<=0) || (genreId3<=0)) return StatusType::INVALID_INPUT;
        if((genreId1 == genreId2) || (genreId2 == genreId3) || (genreId3 == genreId1)) return StatusType::INVALID_INPUT;
        Node* temp1 = genres.find(genreId1);
        Node* temp2 = genres.find(genreId2);
        Node* temp3 = genres.insert(genreId3);
        temp1->getParent()->setParent(temp2->getParent());
        temp2->getParent()->setParent(temp3);
        temp3->setParent(temp2->getParent());
        temp3->setGenreChanges(temp1->getGenreChanges() + temp2->getGenreChanges());
        temp1->setParent(nullptr);
        temp2->setParent(nullptr);
        temp1->setGenreChanges(0);
        temp2->setGenreChanges(0);
    }
    catch (const std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
    catch (const MyFailure&){
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

output_t<int> DSpotify::getSongGenre(int songId){
    try {
        if(songId<=0) return StatusType::INVALID_INPUT;
        Node* temp = songs.find(songId);
        Node* temp2 = temp;
        Node* temp3 = temp;
        while(temp->getParent()->getParent() != temp){
            temp = temp->getParent();
        }
        while(temp2->getParent() != temp){
            temp3 = temp2->getParent();
            temp2->setParent(temp);
            temp2 = temp3;
        }
        return temp->getParent()->getId();
    }
    catch (const std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
    catch (const MyFailure&){
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

output_t<int> DSpotify::getNumberOfSongsByGenre(int genreId){
    try {
        if(genreId<=0) return StatusType::INVALID_INPUT;
        return genres.find(genreId)->getGenreChanges();
    }
    catch (const std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
    catch (const MyFailure&){
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

output_t<int> DSpotify::getNumberOfGenreChanges(int songId){
    try {
        if(songId<=0) return StatusType::INVALID_INPUT;
        return songs.find(songId)->getGenreChanges();
    }
    catch (const std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
    catch (const MyFailure&){
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}
