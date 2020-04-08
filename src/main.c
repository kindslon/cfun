#include <stdio.h>
#include <stdlib.h>

#define CALL(o,f) (o->f(o))

typedef struct MArg
{
    char *name;
    void *val;
} MArg;

typedef struct Method 
{
    char *name;
    void (*func)(MArg *args);
} Method;

typedef struct Object 
{
    struct Object *__self;
    const char *__otype;
    Method *methods; 
    void *(*call)(const char *name, MArg *args);
} Object;

Object *onew(const char *otype, void *obj)
{
    Object *o = (Object*) obj;
    o->__self = o;
    o->__otype = otype;
    return o;
}

typedef struct Shape {
    Object parent;
    void (*ctor)();
    double (*area)();
} Shape;

typedef struct Rectangle 
{
    Shape parent;
    void (*ctor)(double width, double length);
    double width, length;
    double (*area)();
} Rectangle;

double Rectangle_area(Rectangle *self)
{
    return self->width * self->length;
}

Rectangle *Rectangle_new(double width, double length) 
{
    Rectangle *r = malloc(sizeof(Rectangle));
    r->parent.area = r->area = Rectangle_area;
    //r->parent.ctor();
    r->width = width;
    r->length = length;
}

int main()
{
    printf("hi there!\n");
    
    Rectangle *r = Rectangle_new(7, 9);
    //printf("rectangle area: %f\n", r->area(r));
    printf("rectangle area: %f\n", CALL(r, area));

    return 0;
}
