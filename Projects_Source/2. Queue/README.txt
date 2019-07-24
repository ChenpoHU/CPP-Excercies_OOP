For the static_cast to work, we have to define a conversion from one Queue type to another Queue type, which casts every single element inside the Queue. 

dynamic_cast won´t work because we don´t have polymorphic inheritance. Neither is there a virtual member nor is there inheritance, just different template type instances (int and char).