#pragma once

#include "ofMain.h"
#include "ofxImGui.h"

class ListBoxContent
{
public:
    

    ListBoxContent()
    {
        label = "";
        currentIndex = 0;
        heightInLines = 0;
        numItems = 0;
        items = NULL;
        itemCollection.reserve(10);
    }
    
    ~ListBoxContent()
    {
        items = NULL;
        clearItemCollection();
    }
    
    void addItems(vector<string>& items_)
    {
        for(size_t i=0; i<items_.size(); i++)
        {
            addItem(items_[i].c_str());
        }
    }

    void addItems(vector<const char *>& items_)
    {
        for(size_t i=0; i<items_.size(); i++)
        {
            addItem(items_[i]);
        }
    }
    
    void clearItemCollection()
    {
        for(size_t i=0; i<itemCollection.size(); i++)
        {
            delete itemCollection[i];
        }
        itemCollection.clear();
    }
    
    void addItem(const char * itemName)
    {
        names.push_back(ofToString(itemName));
        if(names.size()>itemCollection.capacity())
        {
            //https://stackoverflow.com/questions/21144223/c-str-results-from-vectorstring-become-garbage-with-libc
           
            clearItemCollection();
            itemCollection.reserve(names.size());
            items = NULL;
        }
        
        for(size_t i=0; i<names.size(); i++)
        {
            itemCollection[i] = names[i].c_str();
        }
        items = &itemCollection[0];
        numItems = names.size();
    }
    
    bool render()
    {
        bool result =  ImGui::ListBox(label.c_str(),
                       &currentIndex,
                       items,
                       numItems,
                       heightInLines);
        
        if(result)
        {
            ofLogVerbose() << names[currentIndex];
        }
        return result;
    }
    
    string label;
    int currentIndex;
    int heightInLines;
    const char** items;
    int numItems;
    vector<const char *> itemCollection;
    vector<string> names;
};
