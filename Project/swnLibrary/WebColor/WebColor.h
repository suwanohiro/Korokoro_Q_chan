#pragma once

#include "Mof.h"

#include "../StringAction/StringAction.h"

struct WebColor {
    static inline const char* black                 = "000000";
    static inline const char* dimgray               = "696969";
    static inline const char* gray                  = "808080";
    static inline const char* darkgray              = "a9a9a9";
    static inline const char* silver                = "c0c0c0";
    static inline const char* lightgray             = "d3d3d3";
    static inline const char* gainsboro             = "dcdcdc";
    static inline const char* whitesmoke            = "f5f5f5";
    static inline const char* white                 = "ffffff";
    static inline const char* snow                  = "fffafa";
    static inline const char* ghostwhite            = "f8f8ff";
    static inline const char* floralwhite           = "fffaf0";
    static inline const char* linen                 = "faf0e6";
    static inline const char* antiquewhite          = "faebd7";
    static inline const char* papayawhip            = "ffefd5";
    static inline const char* blanchedalmond        = "ffebcd";
    static inline const char* bisque                = "ffe4c4";
    static inline const char* moccasin              = "ffe4b5";
    static inline const char* navajowhite           = "ffdead";
    static inline const char* peachpuff             = "ffdab9";
    static inline const char* mistyrose             = "ffe4e1";
    static inline const char* lavenderblush         = "fff0f5";
    static inline const char* seashell              = "fff5ee";
    static inline const char* oldlace               = "fdf5e6";
    static inline const char* ivory                 = "fffff0";
    static inline const char* honeydew              = "f0fff0";
    static inline const char* mintcream             = "f5fffa";
    static inline const char* azure                 = "f0ffff";

    static inline const char* aliceblue             = "f0f8ff";
    static inline const char* lavender              = "e6e6fa";
    static inline const char* lightsteelblue        = "b0c4de";
    static inline const char* lightslategray        = "778899";
    static inline const char* slategray             = "708090";
    static inline const char* steelblue             = "4682b4";
    static inline const char* royalblue             = "4169e1";
    static inline const char* midnightblue          = "191970";
    static inline const char* navy                  = "000080";
    static inline const char* darkblue              = "00008b";
    static inline const char* mediumblue            = "0000cd";
    static inline const char* blue                  = "0000ff";
    static inline const char* dodgerblue            = "1e90ff";
    static inline const char* cornflowerblue        = "6495ed";
    static inline const char* deepskyblue           = "00bfff";
    static inline const char* lightskyblue          = "87cefa";
    static inline const char* skyblue               = "87ceeb";
    static inline const char* lightblue             = "add8e6";
    static inline const char* powderblue            = "b0e0e6";
    static inline const char* paleturquoise         = "afeeee";
    static inline const char* lightcyan             = "e0ffff";
    static inline const char* cyan                  = "00ffff";
    static inline const char* aqua                  = "00ffff";
    static inline const char* turquoise             = "40e0d0";
    static inline const char* mediumturquoise       = "48d1cc";
    static inline const char* darkturquoise         = "00ced1";
    static inline const char* lightseagreen         = "20b2aa";
    static inline const char* cadetblue             = "5f9ea0";

    static inline const char* darkcyan              = "008b8b";
    static inline const char* teal                  = "008080";
    static inline const char* darkslategray         = "2f4f4f";
    static inline const char* darkgreen             = "006400";
    static inline const char* green                 = "008000";
    static inline const char* forestgreen           = "228b22";
    static inline const char* seagreen              = "2e8b57";
    static inline const char* mediumseagreen        = "3cb371";
    static inline const char* mediumaquamarine      = "66cdaa";
    static inline const char* darkseagreen          = "8fbc8f";
    static inline const char* aquamarine            = "7fffd4";
    static inline const char* palegreen             = "98fb98";
    static inline const char* lightgreen            = "90ee90";
    static inline const char* springgreen           = "00ff7f";
    static inline const char* mediumspringgreen     = "00fa9a";
    static inline const char* lawngreen             = "7cfc00";
    static inline const char* chartreuse            = "7fff00";
    static inline const char* greenyellow           = "adff2f";
    static inline const char* lime                  = "00ff00";
    static inline const char* limegreen             = "32cd32";
    static inline const char* yellowgreen           = "9acd32";
    static inline const char* darkolivegreen        = "556b2f";
    static inline const char* olivedrab             = "6b8e23";
    static inline const char* olive                 = "808000";
    static inline const char* darkkhaki             = "bdb76b";
    static inline const char* palegoldenrod         = "eee8aa";
    static inline const char* cornsilk              = "fff8dc";
    static inline const char* beige                 = "f5f5dc";

    static inline const char* lightyellow           = "ffffe0";
    static inline const char* lightgoldenrodyellow  = "fafad2";
    static inline const char* lemonchiffon          = "fffacd";
    static inline const char* wheat                 = "f5deb3";
    static inline const char* burlywood             = "deb887";
    static inline const char* tan                   = "d2b48c";
    static inline const char* khaki                 = "f0e68c";
    static inline const char* yellow                = "ffff00";
    static inline const char* gold                  = "ffd700";
    static inline const char* orange                = "ffa500";
    static inline const char* sandybrown            = "f4a460";
    static inline const char* darkorange            = "ff8c00";
    static inline const char* goldenrod             = "daa520";
    static inline const char* peru                  = "cd853f";
    static inline const char* darkgoldenrod         = "b8860b";
    static inline const char* chocolate             = "d2691e";
    static inline const char* sienna                = "a0522d";
    static inline const char* saddlebrown           = "8b4513";
    static inline const char* maroon                = "800000";
    static inline const char* darkred               = "8b0000";
    static inline const char* brown                 = "a52a2a";
    static inline const char* firebrick             = "b22222";
    static inline const char* indianred             = "cd5c5c";
    static inline const char* rosybrown             = "bc8f8f";
    static inline const char* darksalmon            = "e9967a";
    static inline const char* lightcoral            = "f08080";
    static inline const char* salmon                = "fa8072";
    static inline const char* lightsalmon           = "ffa07a";

    static inline const char* coral                 = "ff7f50";
    static inline const char* tomato                = "ff6347";
    static inline const char* orangered             = "ff4500";
    static inline const char* red                   = "ff0000";
    static inline const char* crimson               = "dc143c";
    static inline const char* mediumvioletred       = "c71585";
    static inline const char* deeppink              = "ff1493";
    static inline const char* hotpink               = "ff69b4";
    static inline const char* palevioletred         = "db7093";
    static inline const char* pink                  = "ffc0cb";
    static inline const char* lightpink             = "ffb6c1";
    static inline const char* thistle               = "d8bfd8";
    static inline const char* magenta               = "ff00ff";
    static inline const char* fuchsia               = "ff00ff";
    static inline const char* violet                = "ee82ee";
    static inline const char* plum                  = "dda0dd";
    static inline const char* orchid                = "da70d6";
    static inline const char* mediumorchid          = "ba55d3";
    static inline const char* darkorchid            = "9932cc";
    static inline const char* darkviolet            = "9400d3";
    static inline const char* darkmagenta           = "8b008b";
    static inline const char* purple                = "800080";
    static inline const char* indigo                = "4b0082";
    static inline const char* darkslateblue         = "483d8b";
    static inline const char* blueviolet            = "8a2be2";
    static inline const char* mediumpurple          = "9370db";
    static inline const char* slateblue             = "6a5acd";
    static inline const char* mediumslateblue       = "7b68ee";
};

struct RGBData {
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

static RGBData __getRGBArray(const char* colorCode) {
    std::vector<std::string> colorData = StringAction::Split(colorCode, 2);

    RGBData result;

    unsigned long work[3];
    for (int cnt = 0; cnt < 3; cnt++) {
        work[cnt] = std::stoi(colorData[cnt].c_str(), nullptr, 16);
    }

    result.R = work[0];
    result.G = work[1];
    result.B = work[2];

    return result;
}

static unsigned long getRGB(const char* colorCode) {
    RGBData rgb = __getRGBArray(colorCode);

    return MOF_XRGB(rgb.R, rgb.G, rgb.B);
}

static unsigned long getRGBA(const char* colorCode, unsigned long alpha) {
    RGBData rgb = __getRGBArray(colorCode);

    return MOF_ARGB(alpha, rgb.R, rgb.G, rgb.B);
}
