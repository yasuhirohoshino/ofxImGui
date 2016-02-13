#include "ofApp.h"

#define TEX_ID (ImTextureID)(uintptr_t)

vector<string> strings;
//--------------------------------------------------------------
void ofApp::setup()
{
    
    //ofLogVerbose() << SRCROOT;

    ofSetLogLevel(OF_LOG_VERBOSE);
    
    //required call
    gui.setup();
    
    ImGui::GetIO().MouseDrawCursor = false;
    //backgroundColor is stored as an ImVec4 type but can handle ofColor
    backgroundColor = ofColor(114, 144, 154);
    show_test_window = true;
    show_another_window = false;
    floatValue = 0.0f;
    
    imageButton = gui.loadImage("of.png");
    textureButtonID = gui.loadTexture(textureButton, "of.png");
    
    ofLoadImage(textureButtonPreAllocated, "of.png");
    textureButtonPreAllocatedID = gui.loadTexture(textureButtonPreAllocated);
    
    
    listBoxContent.currentIndex = 1;
    listBoxContent.label = "LISTBOX LABEL";
    listBoxContent.heightInLines = 4;
    
    listBoxContent.addItem("Apple");
    listBoxContent.addItem("Banana");
    listBoxContent.addItem("Cherry");
    listBoxContent.addItem("Kiwi");
    listBoxContent.addItem("Mango");
    
    
    vector<const char *> additionalItems = {"Orange", "Pineapple", "Strawberry", "Watermelon"};
    
    strings.push_back("Orange2");
    strings.push_back("Pineapple2");
    listBoxContent.addItems(additionalItems);
    listBoxContent.addItems(strings);
    
    videoButtonID = -1;
    
    videoPlayer.load("fingers.mov");
    videoPlayer.play();
    
    floatParam.set("test", (float)10.f);
    
    doShowTestWindow.set("", true);
    
   
    ofFbo::Settings fboSettings;
    fboSettings.width = videoPlayer.getWidth();
    fboSettings.height = videoPlayer.getHeight();
    fboSettings.internalformat = GL_RGBA;
    fboSettings.textureTarget = GL_TEXTURE_2D;
    videoFBO.allocate(fboSettings);
    videoButtonID = videoFBO.getTexture().texData.textureID;
}

bool doSetTheme = false;
//--------------------------------------------------------------
void ofApp::update(){
    
    videoPlayer.update();
    videoFBO.begin();
    videoPlayer.draw(0, 0);
    videoFBO.end();
    
    if(doSetTheme)
    {
        doSetTheme = false;
        gui.setTheme(new ThemeTest());
        
    }

    
}

bool ColorEdit3(const char* label, ImVec4& color)
{
    return ImGui::ColorEdit3(label, (float*)&color);
}
bool doThemeColorsWindow = false;
//--------------------------------------------------------------
void ofApp::draw(){
    
    //backgroundColor is stored as an ImVec4 type but is converted to ofColor automatically

    ofSetBackgroundColor(backgroundColor);
    
    //required to call this at beginning
    gui.begin();
    
    if(listBoxContent.draw())
    {
        ofLogVerbose() << "listBoxContent changed to " << listBoxContent.currentIndex;
    }
    
    
    gui.end();
    return;
    //In between gui.begin() and gui.end() you can use ImGui as you would anywhere else
    
    // 1. Show a simple window
    {
        ImGui::Text("Hello, world!");
        ImGui::SliderFloat("Float", &floatValue, 0.0f, 1.0f);
        ImGui::SliderFloat("floatParam", &floatParam.value, 0.0f, 1.0f);
        
        //this will change the app background color
        //ImGui::ColorEdit3("Background Color", (float*)&backgroundColor);
        
        ColorEdit3("Background Color", backgroundColor);
        if(ImGui::Button("Test Window"))
        {
            doShowTestWindow.value = !doShowTestWindow.value;
        }
        
        if (ImGui::Button("Another Window"))
        {
            //bitwise OR
            show_another_window ^= 1;
        
        }
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    } 
    // 2. Show another window, this time using an explicit ImGui::Begin and ImGui::End
    if (show_another_window)
    {
        //note: ofVec2f and ImVec2f are interchangeable 
        ImGui::SetNextWindowSize(ofVec2f(200,100), ImGuiSetCond_FirstUseEver);
        ImGui::Begin("Another Window", &show_another_window);
            ImGui::Text("Hello");
        ImGui::End();
    }
    
    // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
    if (doShowTestWindow.value)
    {
        ImGui::SetNextWindowPos(ofVec2f(650, 20), ImGuiSetCond_FirstUseEver);
        ImGui::ShowTestWindow(&doShowTestWindow.value);
    }
    
    
    bool pressed = ImGui::ImageButton(TEX_ID imageButton, ImVec2(200, 141));
    pressed = ImGui::ImageButton(TEX_ID textureButtonID, ImVec2(200, 200));
    pressed = ImGui::ImageButton(TEX_ID videoButtonID, ImVec2(200, 200));
    pressed = ImGui::ImageButton(TEX_ID textureButtonPreAllocatedID, ImVec2(200, 200));


    

    
    if(doThemeColorsWindow)
    {
        gui.openThemeColorWindow();
        
    }
   


    //required to call this at end
    gui.end();
    
    textureButton.draw(0, 0);
    int w = videoPlayer.getWidth();
    videoFBO.draw(w, 0);
    videoPlayer.draw(w*2, 0);
    videoFBO.getTexture().draw(w*3, 0);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    ofLogVerbose(__FUNCTION__) << key;
    switch (key)
    {
        case 't' :
        {
            doThemeColorsWindow = !doThemeColorsWindow;
            break;
        }
        case 'c' :
        {
            doSetTheme = !doSetTheme;
            break;
        }
        case 's':
        {
            break;
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    ofLogVerbose(__FUNCTION__) << key;
    
}


void ofApp::mouseScrolled(float x, float y)
{
    ofLogVerbose(__FUNCTION__) << "x: " << x << " y: " << y;
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}