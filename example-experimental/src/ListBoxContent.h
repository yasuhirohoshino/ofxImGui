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
        items = NULL;
    }
    
    ~ListBoxContent()
    {
        if(items)
        {
            delete items;
            items = NULL;
        }
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
            if(itemCollection[i])
            {
                //delete itemCollection[i];
                itemCollection[i] = NULL;
            }
            
        }
        itemCollection.clear();
    }
    
    void addItem(const char * itemName)
    {
        int currentSize = itemCollection.size();
        itemCollection[currentSize] = itemName;
        
        if(items)
        {
            delete items;
            items = NULL;
        }
       
        items = (const char**)malloc(sizeof(const char*) * itemCollection.size());

        for(int i=0; i<itemCollection.size(); i++)
        {
            items[i] = itemCollection[i];
        }
    }
    
    bool draw()
    {
        if(!items) return;
        
        bool result =  ImGui::ListBox(label.c_str(),
                       &currentIndex,
                       items,
                       itemCollection.size(),
                       heightInLines);
        
        if(result)
        {
            ofLogVerbose() << itemCollection[currentIndex];
        }
        return result;
    }
    
    string label;
    int currentIndex;
    int heightInLines;
    const char** items;
    map< int, const char *> itemCollection;
};
