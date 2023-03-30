#! /usr/bin/python3.8 

import time

import json
import ujson
import cjson

DEBUG = False


def basic_test():
    json_str_1 = '''
                {"Walter" : "White",
                 "Jesse" : "Pinkman",
                 'First season' : -2008}
                '''

    json_dict_1 = cjson.loads(json_str_1)
    if DEBUG:
        print("test_output", json_dict_1)
    
    dumps_str_cjson = cjson.dumps(json_dict_1)
    dumps_str_json  = json.dumps(json_dict_1)
    if DEBUG:
        print("test dumps", dumps_str_cjson)
        print("json dumps", dumps_str_json)
    assert(dumps_str_cjson == dumps_str_json, "dumps is not same")


def time_test():
    big_json = open("test_json.json", 'r').read()
    if DEBUG:
        print(big_json)
    
    time_begin = time.time()
    json_dict = json.loads(big_json)
    time_end = time.time()

    json_delta_loads = time_end - time_begin

    time_begin = time.time()
    ujson_dict = ujson.loads(big_json)
    time_end = time.time()

    ujson_delta_loads = time_end - time_begin

    time_begin = time.time()
    cjson_dict = cjson.loads(big_json)
    time_end = time.time()

    cjson_delta_loads = time_end - time_begin
    assert(json_dict == ujson_dict == cjson_dict, "dicts not the same")
    if DEBUG:
        print(cjson_dict)

    time_begin = time.time()
    json_str = json.dumps(cjson_dict)
    time_end = time.time()

    json_delta_dumps = time_end - time_begin

    time_begin = time.time()
    ujson_str = ujson.dumps(cjson_dict)
    time_end = time.time()

    ujson_delta_dumps = time_end - time_begin
    if DEBUG:
        print("i am died here")
    time_begin = time.time()
    cjson_str = cjson.dumps(cjson_dict)
    time_end = time.time()

    cjson_delta_dumps = time_end - time_begin
    assert(json_str == ujson_str == cjson_str, "strs not the same")
    if DEBUG:
        print(cjson_str)

    report_str = f"""\tLoads:\n\
    \t\tjson : {json_delta_loads}\n\
    \t\tujson : {ujson_delta_loads}\n\
    \t\tcjson : {cjson_delta_loads}\n\
    \tDumps:\n\
    \t\tjson : {json_delta_dumps}\n\
    \t\tujson : {ujson_delta_dumps}\n\
    \t\tcjson : {cjson_delta_dumps}"""
    
    print(report_str)



def main():
    basic_test()
    time_test()


if __name__ == "__main__":
    main()