#include <stdio.h>
#include <time.h>

#include <string>
#include <map>
#include <fstream>

class VCD_Out {
    std::string pathname;
    time_t              tdate;
    std::fstream        vcdf;
    bool                defns;
    unsigned            last_time;
    unsigned            time;

    struct s_defn 
    {
        char        chref;
        std::string name;
        int         value;
        int         size;
    };

    std::map<int,s_defn> wires;
    void write_defns();

public:
    VCD_Out();
    ~VCD_Out();

    inline const char *get_pathname() {
        return pathname.c_str();
    }

    bool open(const char *path,double n,const char *units,const char *vers);
    void define_binary(int ref,const char *name);
    void define_vector(int ref,size_t size, const char *name);

    void set_time(unsigned t);
    void increment_time_ms(unsigned t);
    void set_value(int ref,int value);
};

// End vcdout.hpp
