# IconFontCppHeaders

[https://github.com/juliettef/IconFontCppHeaders](https://github.com/juliettef/IconFontCppHeaders)

C++11 and C89 headers for icon fonts Font Awesome, Fork Awesome, Google Material Design icons, Kenney game icons and Ionicons.

A set of header files for using icon fonts in C and C++, along with the python generator used to create the files.

Each header contains defines for one font, with each icon code point defined as ICON_*, along with the min and max code points for font loading purposes.

## Fonts

* [Font Awesome](http://fontawesome.io/)  
    * [GitHub repository](https://github.com/FortAwesome/Font-Awesome/)
    * Font Awesome 4 
        * [fontawesome-webfont.ttf](https://github.com/FortAwesome/Font-Awesome/blob/fa-4/fonts/fontawesome-webfont.ttf)
    * Font Awesome 5 
        * [fa-solid-900.ttf](https://github.com/FortAwesome/Font-Awesome/blob/master/web-fonts-with-css/webfonts/fa-solid-900.ttf)
        * [fa-regular-400.ttf](https://github.com/FortAwesome/Font-Awesome/blob/master/web-fonts-with-css/webfonts/fa-regular-400.ttf)
        * [fa-brands-400.ttf](https://github.com/FortAwesome/Font-Awesome/blob/master/web-fonts-with-css/webfonts/fa-brands-400.ttf)
* [Fork Awesome](https://forkawesome.github.io/Fork-Awesome/)
    * [GitHub repository](https://github.com/ForkAwesome/Fork-Awesome)
    * [forkawesome-webfont.ttf](https://github.com/ForkAwesome/Fork-Awesome/blob/master/fonts/forkawesome-webfont.ttf)
* [Google Material Design icons](https://design.google.com/icons/) 
    * [GitHub repository](https://github.com/google/material-design-icons/)
    * [MaterialIcons-Regular.ttf](https://github.com/google/material-design-icons/blob/master/iconfont/MaterialIcons-Regular.ttf)
* [Kenney Game icons](http://kenney.nl/assets/game-icons) and [Game icons expansion](http://kenney.nl/assets/game-icons-expansion) 
    * [GitHub repository](https://github.com/nicodinh/kenney-icon-font/)
    * [kenney-icon-font.ttf](https://github.com/nicodinh/kenney-icon-font/blob/master/fonts/kenney-icon-font.ttf)
* [Ionicons](http://ionicons.com/)
    * [GitHub repository](https://github.com/ionic-team/ionicons)
    * [ionicons.ttf](https://github.com/ionic-team/ionicons/blob/master/fonts/ionicons.ttf)

### Font Awesome 5 notes

Font Awesome 5 splits the different styles of icons into different font files: solid, regular and brands  

* identical font codepoints for styles *solid* and *regular* (regular is a subset of solid) icon font file; 
* a different set of codepoints for style *brands* icon font file  

We have put the brands into a different header file, as the brands codepoints are mixed with the standard icons' so the fonts cannot easily be used without switching between the two fonts in your code.

The codepoints only cover the free fonts.

## Example Code

Using [dear imgui](https://github.com/ocornut/imgui) as an example UI library:

```Cpp
    
    #include "IconsFontAwesome5.h"
    
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontDefault();
     
    // merge in icons from Font Awesome
    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
    io.Fonts->AddFontFromFileTTF( FONT_ICON_FILE_NAME_FAS, 16.0f, &icons_config, icons_ranges );
    // use FONT_ICON_FILE_NAME_FAR if you want regular instead of solid
    
    // in an imgui window somewhere...
    ImGui::Text( ICON_FA_PAINT_BRUSH "  Paint" );    // use string literal concatenation
    // outputs a paint brush icon and 'Paint' as a string.
```

## Projects using the font icon header files

## [Avoyd](https://www.avoyd.com)
Avoyd is an abstract 6 degrees of freedom voxel game. The voxel editor's Edit Tool UI uses [dear imgui](https://github.com/ocornut/imgui) with [Font Awesome](http://fontawesome.io/) icon fonts.  
  
![Avoyd Edit Tool with Font Awesome fonts](https://storage.googleapis.com/enkisoftware-images/Avoyd_2017-11-18_v0.14.220_Dear_imGui_FontAwesome.jpg)

## [bgfx](https://github.com/bkaradzic/bgfx)
Cross-platform rendering library.

## Credits

Development - [Juliette Foucaut](http://www.enkisoftware.com/about.html#juliette) - [@juliettef](https://github.com/juliettef)  
Requirements - [Doug Binks](http://www.enkisoftware.com/about.html#doug) - [@dougbinks](https://github.com/dougbinks)  
[None](https://bitbucket.org/duangle/nonelang/src) language implementation and [refactoring](https://gist.github.com/paniq/4a734e9d8e86a2373b5bc4ca719855ec) - [Leonard Ritter](http://www.leonard-ritter.com/) - [@paniq](https://github.com/paniq)  
Suggestion to add a define for the ttf file name - [Sean Barrett](https://nothings.org/) - [@nothings](https://github.com/nothings)  
Initial Font Awesome 5 implementation - [Codecat](https://codecat.nl/) - [@codecat](https://github.com/codecat)  
Suggestion to add Fork Awesome - [Julien Deswaef](http://xuv.be/) - [@xuv](https://github.com/xuv)  
Suggestion to add Ionicons - [Omar Cornut](http://www.miracleworld.net/) - [@ocornut](https://github.com/ocornut)  
