#ifndef BIG_ENDIAN_MEMORY_H
#define BIG_ENDIAN_MEMORY_H

#include <stdint.h>
#include <string.h>
#include "bits.h"

class Memory {
public:
   static uint8_t* allocate(uint64_t address, unsigned size);
   static void free(uint64_t address, unsigned size);

   static inline void set(uint64_t address, uint8_t value, uint64_t size)
   {
      memset(reinterpret_cast<void*>(address), value, size);
   }

   static inline void zero(uint64_t address, uint64_t size)
   {
      memset(reinterpret_cast<void*>(address), 0, size);
   }

   template<typename Type>
   static inline Type translate(Type address)
   {
      return (Type)(((uint64_t)address) & 0xFFFFFFFF);
   }

   template<typename T>
   static inline T read(uint64_t address)
   {
      return bits::swap(*reinterpret_cast<T*>(translate(address)));
   }

   template<typename PointedType>
   static inline PointedType read(PointedType *address)
   {
      return read<PointedType>(reinterpret_cast<uint64_t>(address));
   }

   template<typename T>
   static inline void write(uint64_t address, const T &value)
   {
      *reinterpret_cast<T*>(translate(address)) = bits::swap<T>(value);
   }

   template<typename PointedType>
   static inline void write(PointedType * address, const PointedType &value)
   {
      return write<PointedType>(reinterpret_cast<uint64_t>(address), value);
   }
   
private:
};

#endif //BIG_ENDIAN_MEMORY_H
