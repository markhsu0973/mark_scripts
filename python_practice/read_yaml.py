#! /usr/bin/env python
import yaml


def main():
    with open('RPR_param.yaml', 'r') as stream:
        data = yaml.load(stream, Loader=yaml.CLoader)

    print "==="
    for mode in data:
        print mode
        for pkg in data[mode]:
            print "\t",pkg
            if data[mode][pkg]:
                for parameter in data[mode][pkg]:
                        print "\t\t",parameter 
                        print "\t\t\t",data[mode][pkg][parameter]
    print "==="
    dic = dict()
    dic['test'] = data["narrow_lane"]
    data['default'] = dic['test']
    mode = "narrow_lane"
    print "mode = ", mode
    for pkg in data[mode]:
            clint_name = pkg
            param = data[mode][pkg]
            print "\tdynamic_reconfigure.client.Client( " + "'"+ clint_name + "'"+", timeout=10)"
            print "\t\tparam = ", param

    mode = "default"
    print "mode = ", mode
    for pkg in data[mode]:
            clint_name = pkg
            param = data[mode][pkg]
            print "\tdynamic_reconfigure.client.Client( " + "'"+ clint_name + "'"+", timeout=10)"
            print "\t\tparam = ", param

if __name__ == '__main__':
    main()