#include "zonemaps.h"

template<typename T>
zonemap<T>::zonemap(std::vector<T> _elements, uint _num_elements_per_zone)
    : elements(std:: move(_elements)), num_elements_per_zone(_num_elements_per_zone)
{
    // constructor 
    // Your code starts here ...
    if(num_elements_per_zone<1){
        throw std::invalid_argument("Please enter a number greater than 0")
    }
    if(elements.empty()){
        num_zones = 0;
        return;
    }
    build();
}

template<typename T>
void zonemap<T>::build(){
    sort_elements();
    num_zones = (total + num_elements_per_zone -1)/ num_elements_per_zone;
    zone<T> current;
    for(size_t i = 0; i < elements.size(); i++){
        current.elements.push_back(elements[i]);
        if(current.elements.size()==num_elements_per_zone || i == elements.size()-1){
            current_zone.min = current_zone.elements.front();
            current_zone.max = current_zone.elements.back();
            current_zone.size = current_zone.elements.size();
        }
        zones.push_back(std::move(current_zone));
        current_zone.elements.clear();

    }
}

template<typename T>
void zonemap<T>::sort_elements(){
    bool swapped;
    int n = elements.size();
    for(size_t i = 0; i < n-1; i++){
        swapped = false;
        for(size_t j = 0; j < n-1; j++){
            if(elements[j]> elements[j+1]){
                std::swap(elements[j],elements[j+1]);
                swapped = true;
            }
        }
        if(!swapped){
            break;
        }
    }
}

template<typename T>
size_t zonemap<T>::query(T key)
{
    // Your code starts here ...
    size_t count = 0;
    for(size_t i= 0; i < num_zones; i++){
        const auto& z = zones[i];
        if(z.max >= key && z.min <= key){
            for (const auto& element : z.elements) {
            if (element == key) {
                count++;  
            }
        }
        }
    }
    return count;
}

template<typename T>
std::vector<T> zonemap<T>::query(T low, T high){
    std::vector<T> result;
    for(const auto&z : zones){
        if(z.max >= low && z.min <= high){
            for(const auto&e : z.elements){
                if(e >= low && e <= high){
                    result.push_back(e);
                }
            }
        }
    }
    return result;
}

