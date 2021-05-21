
#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    // Create an unordered_map of three strings (that map to strings)
    std::unordered_map<std::string, std::string> umap = {
        {"RED","#FF0000"},
        {"GREEN","#00FF00"},
        {"BLUE","#0000FF"}
    };

    // Iterate and print keys and values of unordered_map
    for( const auto& n : umap ) {
        std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    }

    // Add two new entries to the unordered_map
    umap["BLACK"] = "#000000";
    umap["WHITE"] = "#FFFFFF";

    // Output values by key
    std::cout << "The HEX of color RED is:[" << umap["RED"] << "]\n";
    std::cout << "The HEX of color BLACK is:[" << umap["BLACK"] << "]\n";

    return 0;
}