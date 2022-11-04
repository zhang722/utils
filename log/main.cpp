#include "include/log.h"

int main(){
    log::info("this is {+.2f} format {afdafd} aaa{}", 21.34, "ser");
    log::debug("this is {+.2f} format {afdafd} aaa{}", 21.34, "ser");
    log::warn("this is {+.2f} format {afdafd} aaa{}", 21.34, "ser");
}