#include "include/log.h"

int main(){
    info("this is {+.2f} format {afdafd} aaa{}", 21.34, "ser");
    debug("this is {+.2f} format {afdafd} aaa{}", 21.34, "ser");
    warn("this is {+.2f} format {afdafd} aaa{}", 21.34, "ser");
}