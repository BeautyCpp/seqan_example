
#include <seqan/index.h>
#include <catch.hpp>
#include <iostream>

using namespace seqan;

TEST_CASE("index", "[basic]")
{

    typedef Index<CharString> TIndex;
    TIndex index("mississippi");

    SECTION("SuffixArrayIndex")
    {
        using TText = String<char>;
        using TIndex = Index<TText>;
        TText text("mississippi");
        TIndex index(text);
        clear(index);
        countSequences(index);
        indexCreate(index, FibreSA());
    }
    SECTION("Fibre")
    {
        using TText = String<char>;
        using TIndex = Index<TText>;

    }
    SECTION("StringSet") 
    {
        using TText = StringSet<String<char>>;
        using TIndex = Index<TText>;

        //text
        TText text;
        appendValue(text, "mississippi");
        appendValue(text, "mississippi");
        //index
        TIndex index(text);
        //iterator
        Iterator<TIndex, TopDown<> >::Type it(index);

        goDown(it, "s");
        std::cout<<"s occur in = "<< representative(it) << std::endl;
        std::cout<<"s fre = " <<getFrequency(it) <<std::endl;

        auto occrs = getOccurrences(it);
        for(auto & v : occrs ) {
            std::cout<<"Hit in sequence "<< v.i1 <<" at position "<<v.i2 << std::endl;
        }
        std::cout<<"===================="<<std::endl; 
        auto r = range(it);
        auto & fibre = getFibre(index, FibreSA());
        for(auto i = r.i1; i < r.i2 ; ++i) {
            
            std::cout<<"Hit in sequence "<< fibre[i].i1 <<
            " at position "<< fibre[i].i2 << std::endl;
        }
    }

    SECTION("String")
    {
        using TText = String<char>;
        using TIndex = Index<TText>;
        TText text = "mississippi";
        TIndex index(text);
        Iterator<TIndex, TopDown<> >::Type it(index);
        goDown(it, "sis");
        std::cout<<"si occur in = "<< representative(it) << std::endl;
        std::cout<<"si fre = " <<getFrequency(it) <<std::endl;

        auto occrs = getOccurrences(it);
        for(auto & v : occrs ) {
            std::cout<<"Hit in position "<< v  << std::endl;
        }
        std::cout<<"===================="<<std::endl; 
        auto r = range(it);
        auto & fibre = getFibre(index, FibreSA());
        for(auto i = r.i1; i < r.i2 ; ++i) {
            std::cout<<"Hit in sequence "<< fibre[i]  << std::endl;
        }
    }

    SECTION("index") 
    {
        using TText  = StringSet<String<char>>;
        using TIndex = Index<TText>;
        TText text;
        appendValue(text, "12345ij");
        appendValue(text, "abcdeij");
        
        TIndex index(text);
        Finder<TIndex> finder(index);
        std::cout<<"length(index)="<<length(index)<<std::endl;
        std::cout<<"countSequence="<<countSequences(index)<<std::endl; 
        while(find(finder, "ij"))
            std::cout<<"Hit="<<position(finder)<<std::endl;
    }

    SECTION("iterator over with ParentLinks")
    {
        Iterator<TIndex, TopDown<ParentLinks<>>>::Type it(index);
        int i = 0;
        do
        {
            // Print the letters from the root to the current node
            std::cout << i++ << "\t" << representative(it) << std::endl;
            if (!goDown(it) && !goRight(it))
                while (goUp(it) && !goRight(it))
                    ;
        } while (!isRoot(it));
        std::cout<<"======================================"<<std::endl;
    }

    SECTION("iterator, postorder")
    {
        Iterator<TIndex, TopDown<ParentLinks<Postorder>>>::Type it(index);
        int i = 0;
        goBegin(it);
        while (!atEnd(it))
        {
            std::cout <<i++ << "\t" << representative(it) << std::endl;
            ++it;
        }
        std::cout<<"======================================"<<std::endl;
    }

    SECTION("iterator, preorder")
    {
        Iterator<TIndex, TopDown<ParentLinks<Preorder>>>::Type it(index);
        int i = 0;
        goBegin(it);
        while (!atEnd(it))
        {
            std::cout <<i++ << "\t" << representative(it) << std::endl;
            ++it;
        }        
        std::cout<<"======================================"<<std::endl;
    }
}
