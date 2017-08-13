#include <seqan/index.h>
#include <catch.hpp>
#include <iostream>

using namespace seqan;

TEST_CASE("fibre", "[basic]")
{
    using TIndex = Index<CharString> ;
    using TText = CharString;
    TText text("^BANANA|");
    TIndex index(text);

    SECTION("esa")
    {
        clear(index);
        indexRequire(index, FibreSA());
        std::cout<<"i\ttext[i]\tsaAt(i)\ttextPos\tBWT\tSuffic\tSA"<<std::endl; 
        for(unsigned i = 0; i < length(indexSA(index));++i) { // i: index for suffix array
            auto sai = saAt(i,index);  //index for the first letter of suffix in text 
            auto s = suffix(text,sai); 
            unsigned textPos = (sai==0) ? length(index) - 1 : sai -1;
            std::cout
            <<i
            <<"\t"<<text[i]
            <<"\t"<<saAt(i,index)
            <<"\t"<<textPos
            <<"\t"<<textAt(textPos, index)
            <<"\t"<<suffix(indexText(index), textPos)
            <<"\t"<<s
            <<std::endl;
        }
        std::cout<<"============================"<<std::endl;
        std::cout<<"length(index)="<<length(index);
        std::cout<<indexSA(index)<<std::endl;
        std::cout<<indexText(index)<<std::endl;

        //clear(index);
        save(index, "saindex");
        indexRawText(index);
        std::cout<< typeid(indexSA(index)).name()<<std::endl;
    }
}