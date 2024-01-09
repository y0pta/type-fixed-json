#include "FixedJson.h"

std::string fixed_json::to_str(fixed_json::EClassType name){
    switch (name){
        case eBinance: return "Binance";
        case eBybit: return "Bybit";
        case eOkx: return "Okx";
        case eDxDy: return "DxDy";
        default: return "Unknown";
    }
}