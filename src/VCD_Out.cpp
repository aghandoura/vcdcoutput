#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <bitset>

#include "VCD_Out.hpp"

VCD_Out::VCD_Out() {
    defns = false;
}

VCD_Out::~VCD_Out() {
    if ( vcdf.is_open() )
    {
        vcdf.close();
    }
}

bool
VCD_Out::open(const char *path,double n,const char *units,const char *vers) {

    if ( vcdf.is_open() )
    {
        vcdf.close();
    }

    vcdf.open(path, std::fstream::out);
    pathname = path;
    if ( !vcdf.is_open() )
        return false;

    tdate = ::time(0);
    {
        struct tm tc;
        char tbuf[256];
    
        localtime_r(&tdate,&tc);
        strftime(tbuf,sizeof tbuf,"%Y-%m-%d %H:%M:%S",&tc);

        vcdf<< "$date" << std::string(tbuf) <<  " $end\n";
    }

    vcdf << "$version" + std::string(vers)  + " $end\n";
    vcdf << "$timescale " << n  << "ms $end\n";

    vcdf << "$scope module top $end\n";
    vcdf.flush();

    defns = false;
    last_time = ~0u;
    time = 0;

    return true;
}

void
VCD_Out::define_vector(int ref,size_t size, const char *name)
{
    size_t n = wires.size();
    s_defn defn;

    if ( n < 26 )
        defn.chref = 'A' + n;
    else
        defn.chref = 'a' + n - 26;
    defn.name = name;
    defn.value = -1;
    defn.size = size;
    wires[ref] = defn;
}


void
VCD_Out::define_binary(int ref,const char *name)
{

    define_vector(ref, 1, name);
}

void
VCD_Out::write_defns()
{

    assert(vcdf);
    for ( auto it = wires.cbegin(); it != wires.cend(); ++it )
    {
        const s_defn& defn = it->second;

        vcdf << "$var wire " << defn.size << " " 
             << defn.chref << " " <<  defn.name << " $end\n";
    }    
    vcdf.flush();
    defns = true;
}

void
VCD_Out::set_time(unsigned t)
{

    if ( !defns )
        write_defns();

    time = t;
}

void
VCD_Out::increment_time_ms(unsigned int t)
{

    if ( !defns )
        write_defns();

    time += t;
}

void
VCD_Out::set_value(int ref,int value)
{

    if ( !defns ) {
        write_defns();
        set_time(0);
    }

    auto it = wires.find(ref);
    assert(it != wires.end());

    s_defn& defn = it->second;
    if ( defn.value!= int(value) ) 
    {
        if ( time != last_time ) {
            vcdf << "#" << time << "\n";
            last_time = time;
        }

        defn.value = int(value);
        if (defn.size == 32 )
        {
            vcdf<<"b";
            std::bitset<32> bits(value);
            vcdf  << bits.to_string() << " " << defn.chref << " \n";
        }
        else if (defn.size > 1)
        {
            vcdf<<"b";
            std::bitset<sizeof(value) * 8> bits(value);
            vcdf  << bits.to_string() << " " << defn.chref << " \n";
        }
        else
        {
            vcdf << (value ? 1:0) <<  defn.chref << " \n";
        }


    }
}

