#pragma once

template <typename T>
class Vector
{
public:
  Vector()
  {
  }

  void
  reserve(int num)
  {
    this->size = num;
    this->elements = 0;
    this->array = std::make_shared<T[]>(num);
    printf("\nReserve with num = %d\n", num);
  }

  void
  add(T&& val)
  {
    if (elements == size)
    {
      fprintf(stderr, "ERROR: Invalid operation, elements = %d, size = %d! %s %s %d\n",
               elements, size, __FILE__, __func__, __LINE__);
      return;
    }

    this->array.get()[this->elements] = std::move(val);
    this->elements++;
  }

  void
  print()
  {
    printf("\nElements: %d\n", elements);
    for(int i = 0; i < elements; i++)
    {
      printf("Element: %d: ", i);
      array.get()[i].print();
    }
  }

  auto
  get_array()
  {
    return this->array;
  }

  auto
  get_elements()
  {
    return this->elements;
  }

  void
  pop()
  {
    if(elements == 0)
    {
      fprintf(stderr, "ERROR: Invalid operation! %s %s %d\n",
               __FILE__, __func__, __LINE__);
      return;
    }
 
    elements--;
  }

private:
  int elements;
  int size;
  std::shared_ptr<T[]> array;
};
