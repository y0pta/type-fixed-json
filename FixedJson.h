#ifndef FIXEDJSON_H
#define FIXEDJSON_H
#include <iostream>
#include <algorithm>
#include <hv/json.hpp>
#define CONSTRAINT_RANGE(...) hv::Json{__VA_ARGS__}
#define CONSTRAINT_ARRAY hv::Json()
#define CONSTRAINT_NUMBER hv::Json(1)
#define CONSTRAINT_FLOAT hv::Json(1.1)
#define CONSTRAINT_STRING hv::Json("s")
#define CONSTRAINT_BOOL hv::Json(true)

namespace fixed_json{
    enum EClassType {
        eBinance,
        eBybit,
        eOkx,
        eDxDy,
        eUnknown
    };
    std::string to_str(EClassType name);
}

using TypeConstraint = nlohmann::json;
using AllowedFields = std::vector<std::string>;
using Value = nlohmann::json::value_t;

template <fixed_json::EClassType ClassType>
class FixedJson {
public:
    FixedJson(int type): _type_id(type){}

    int type_id() const {return _type_id;}
    virtual std::string type_id_str() const {return "";}

    int class_id() const { return ClassType;}
    std::string class_id_str() const {return fixed_json::to_str(fixed_json::EClassType(_type_id));}

    AllowedFields fields() const { return _ALLOWED_FIELDS.at(_type_id);}

    virtual nlohmann::json to_json() const { return _fields;}
    std::string to_str(const int indent = -1) const { return _fields.dump(indent);}

    /**
     * @brief Set-function for request fields. Checks if field is allowable and if value is of correct type.
     * @throws invalid_argument if field is not allowable or value is not of correct type
     */
    void set(const std::string& field, const nlohmann::json& value){
        //TODO: add int range support
        // check field
        auto& allowed_fields = _ALLOWED_FIELDS.at(_type_id);
        if (std::find(allowed_fields.begin(), allowed_fields.end(), field) != allowed_fields.end()){
            throw std::invalid_argument(fixed_json::to_str(ClassType) + ": field '" + field + "' is not valid for '" + type_id_str() + "' request type.");
        }
        // check value type
        if (_ALLOWED_VALUES.contains(field)){
            // check if value is of correct type
            bool check = _ALLOWED_VALUES.at(field).type() == value.type();
            // check if value is in fixed range
            if (_ALLOWED_VALUES.at(field).is_array()){
                // empty range => any value is acceptable
                check = _ALLOWED_VALUES.at(field).empty();
                for (auto& allowableValue: _ALLOWED_VALUES.at(field))
                    if (allowableValue == value) check = true;
            }

            if (!check){
                throw std::invalid_argument(type_id_str() + ": field '" + field + "' has invalid value. Allowed values: " + _ALLOWED_VALUES.at(field).dump(1));
            }
        }
        _fields[field] = value;
    }

protected:

    static std::unordered_map<int, AllowedFields> _ALLOWED_FIELDS; /// map  {_type_id,  allowable fields}
    static std::unordered_map<std::string, TypeConstraint> _ALLOWED_VALUES; /// map { field name, allowed values}

    const int _type_id;
private:
    nlohmann::json _fields; //nlohmann::ordered_json _fields;
};



#endif //FIXEDJSON_H
