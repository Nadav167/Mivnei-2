
#include "dspotify25b2.h"
#include <iostream>
#include "wet2util.h"
#include "HashMap.h"
#include "Node.h"


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
            temp2->setGenreChanges(0 - temp2->getParent()->getGenreChanges());
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
        if(!temp1->getParent() || !temp2->getParent()) {
            if(temp1->getParent() && !temp2->getParent()) {
                temp1->getParent()->setParent(temp3);
                temp3->setParent(temp1->getParent());
                temp1->setParent(nullptr);
                temp3->setGenreChanges(temp1->getGenreChanges());
                temp1->setGenreChanges(0);
            }
            if(!temp1->getParent() && temp2->getParent()) {
                temp2->getParent()->setParent(temp3);
                temp3->setParent(temp2->getParent());
                temp2->setParent(nullptr);
                temp3->setGenreChanges(temp2->getGenreChanges());
                temp2->setGenreChanges(0);
            }
        }
        else {
            temp1->getParent()->setParent(temp2->getParent());
            temp1->getParent()->setGenreChanges(temp1->getParent()->getGenreChanges() - temp2->getParent()->getGenreChanges());
            temp2->getParent()->setParent(temp3);
            temp3->setParent(temp2->getParent());
            temp3->setGenreChanges(temp1->getGenreChanges() + temp2->getGenreChanges());
            temp1->setParent(nullptr);
            temp2->setParent(nullptr);
            temp1->setGenreChanges(0);
            temp2->setGenreChanges(0);

        }
        if(temp3->getGenreChanges() != 0) temp3->getParent()->updateGenreChange();
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
        Node* temp = update(songId);
        if(temp->getParent()->getParent() == temp) {
            return temp->getParent()->getId();
        }
        return temp->getParent()->getParent()->getId();
    }
    catch (const std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
    catch (const MyFailure&){
        return StatusType::FAILURE;
    }

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
}

output_t<int> DSpotify::getNumberOfGenreChanges(int songId){
    try {
        if(songId<=0) return StatusType::INVALID_INPUT;
        Node* temp = update(songId);
        if(temp->getParent()->getParent() == temp) {
            return temp->getGenreChanges() + 1;
        }
        return temp->getGenreChanges() + temp->getParent()->getGenreChanges() + 1;
    }
    catch (const std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
    catch (const MyFailure&){
        return StatusType::FAILURE;
    }
}

Node* DSpotify::update(int songId) {
    int sum = 0;
    Node* temp = songs.find(songId);
    Node* temp2 = temp;
    while(temp->getParent()->getParent() != temp){
        sum += temp->getGenreChanges();
        temp = temp->getParent();
    }
    while(temp2 != temp && temp2->getParent() != temp){
        int tempSum = temp2->getGenreChanges();
        Node* temp3 = temp2->getParent();
        temp2->setGenreChanges(sum);
        sum -= tempSum;
        temp2->setParent(temp);
        temp2 = temp3;
    }
    return songs.find(songId);
}