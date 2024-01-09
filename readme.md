# FixedJson Class

The `FixedJson` class is a C++ template class that provides a way to handle JSON objects with fixed fields and values. It is templated on an enumeration `fixed_json::EClassType`.

## Class Methods

- `FixedJson(int type)`: Constructor that initializes the `_type_id` member variable.
- `type_id()`: Returns the `_type_id` of the object.
- `type_id_str()`: Virtual function that returns an empty string. It's meant to be overridden in derived classes.
- `class_id()`: Returns the `ClassType`, which is a template parameter.
- `class_id_str()`: Converts the `_type_id` to a string representation.
- `fields()`: Returns the allowed fields for the current `_type_id`.
- `to_json()`: Virtual function that returns the `_fields` member variable as a JSON object. It's meant to be overridden in derived classes.
- `to_str()`: Dumps the `_fields` member variable into a string with a specified indentation.
- `set()`: Sets a field in the `_fields` member variable to a specified value. It first checks if the field is allowed and if the value is of the correct type. If the field is not allowed or the value is not of the correct type, it throws an `std::invalid_argument` exception.

## Class Members

- `_ALLOWED_FIELDS`: Static member variable that maps `_type_id` to a set of allowable fields.
- `_ALLOWED_VALUES`: Static member variable that maps field names to their allowed values.
- `_type_id`: Member variable that stores the type ID of the object.
- `_fields`: Member variable that stores the fields of the JSON object.

## Usage

To use the `FixedJson` class, include the `FixedJson.h` header file in your source code. Create an instance of the class with the desired `EClassType`, and use the provided methods to manipulate the JSON object.
```
#include "FixedJson.h"

#include "FixedJson.h"

// Define and initialize _ALLOWED_FIELDS
std::unordered_map<int, AllowedFields> FixedJson<fixed_json::EClassType>::_ALLOWED_FIELDS = {
    {fixed_json::eBinance, {"field1", "field2", "field3"}}
};

// Define and initialize _ALLOWED_VALUES
std::unordered_map<std::string, TypeConstraint> FixedJson<fixed_json::EClassType>::_ALLOWED_VALUES = {
    {"field1", CONSTRAINT_NUMBER},
    {"field2", CONSTRAINT_STRING},
    {"field3", CONSTRAINT_BOOL}
};

int main() {
    // Create an instance of FixedJson with eBinance as the template parameter
    FixedJson<fixed_json::eBinance> json(1);

    // Set fields
    json.set("field1", 123);
    json.set("field2", "Hello, World!");
    json.set("field3", true);

    // Print the type_id
    std::cout << "Type ID: " << json.type_id() << std::endl;

    // Print the class_id
    std::cout << "Class ID: " << json.class_id() << std::endl;

    // Print the class_id_str
    std::cout << "Class ID String: " << json.class_id_str() << std::endl;

    // Get the allowed fields
    AllowedFields allowedFields = json.fields();
    std::cout << "Allowed Fields: ";
    for (const auto& field : allowedFields) {
        std::cout << field << " ";
    }
    std::cout << std::endl;

    // Convert to JSON and print
    nlohmann::json jsonObj = json.to_json();
    std::cout << "JSON: " << jsonObj << std::endl;

    // Convert to string and print
    std::cout << "String: " << json.to_str() << std::endl;

    return 0;
}
```
This will output the JSON object as a string with the specified indentation.
