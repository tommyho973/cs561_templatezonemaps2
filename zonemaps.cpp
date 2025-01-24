#include "zonemaps.h"
#include <algorithm>

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
    //Call function to build zonemap
    build();
}

template<typename T>
void zonemap<T>::build(){
    //Sort elements first
    sort_elements();
    //Calculate the number of zones
    size_t num_elements = elements.size();
    num_zones = std::ceil(static_cast<double>(num_elements)/ num_elements_per_zone);
    zone<T> current_zone;
    //Iterate over all the elements
    for(size_t i = 0; i < elements.size(); i++){
        //Add elements to current_zone
        current_zone.elements.push_back(elements[i]);
        //If the number of elements in the current zone equals the amount of elements per zone or we run out of overall elements then we set the minimum, maximum and size.
        if(current_zone.elements.size()==num_elements_per_zone || i == elements.size()-1){
            //Since the elements are sorted the 1st and last element will be the minimum and maximum
            current_zone.min = current_zone.elements.front();
            current_zone.max = current_zone.elements.back();
            current_zone.size = current_zone.elements.size();
        }
        //Add the zone to the zonemap
        zones.push_back(std::move(current_zone));
        //Clear the current zone
        current_zone.elements.clear();

    }
}

//Using built in sort function I found on Google
template<typename T>
void zonemap<T>::sort_elements(){
    std::sort(elements.begin(),elements.end());
}

template<typename T>
size_t zonemap<T>::query(T key)
{
    // Your code starts here ...
    size_t count = 0;
    //Iterate over the zones
    for(size_t i= 0; i < num_zones; i++){
        const auto& z = zones[i];
        //If key is in the range of the zone iterate over the elements in the zone and increment the count if we have a matching key
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
    //Iterate over the zones
    for(const auto&z : zones){
        //If range exists in the zone range then we add complying elements to our result vector
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

