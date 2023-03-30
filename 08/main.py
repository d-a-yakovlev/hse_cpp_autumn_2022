#! /usr/bin/python3.8 

import time

import json
import cjson

def basic_test():
    json_str_1 = '''
                {"Walter" : "White",
                 "Jesse" : "Pinkman",
                 'First season' : 2008}
                '''

    json_dict_1 = cjson.loads(json_str_1)
    print("test_output", json_dict_1)
    # print(cjson.dumps({}))


def main():
    basic_test()


if __name__ == "__main__":
    main()