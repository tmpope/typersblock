#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

using namespace rapidjson;
using namespace std;

int main() {
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    
    writer.StartObject();
    writer.String("hello");
    writer.String("world");
    writer.String("t");
    writer.Bool(true);
    writer.String("f");
    writer.Bool(false);
    writer.String("n");
    writer.Null();
    writer.String("i");
    writer.Uint(123);
    writer.String("pi");
    writer.Double(3.1416);
    writer.String("a");
    writer.StartArray();
    for (unsigned i = 0; i < 4; i++)
        writer.Uint(i);
    writer.EndArray();
    writer.EndObject();
    writer.StartObject();
    writer.String("type");
    writer.String("success");
    writer.String("user");
    writer.String(user.c_str());
    writer.String("error");
    writer.Bool(false);
    writer.String("level");
    writer.Uint(1);
    writer.String("id");
    writer.Uint(0);
    writer.String("scores");
    writer.StartArray();
    for (unsigned i = 0; i < 4; i++)
        writer.Uint(5);
    writer.EndArray();
    writer.String("subObject");
    writer.StartObject();
    writer.String("field1");
    writer.Uint(1);
    writer.String("field2");
    writer.Uint(2);
    writer.EndObject();
    writer.EndObject();

    cout << s.GetString() << endl;

    return 0;
}