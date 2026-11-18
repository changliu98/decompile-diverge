namespace std {

template <typename T>
void swap(T* first, T* second) {
    T temp = *first;
    *first = *second;
    *second = temp;
}

// Explicit instantiation for function pointers
template void swap<std::__function::__policy const*>(size_t* first, size_t* second);

} // namespace std