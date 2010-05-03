
#include "spec_helper.h"

const float epsilon = 0.000001f;

describe(simd4f, "sanity") {
    it("VECTORIAL_SIMD_TYPE should be defined to a string") {
        std::cout << "Simd type: " << VECTORIAL_SIMD_TYPE << std::endl;
    }
}

describe(simd4f, "creating") {
    
    it("should be possible to create with params") {
        
        simd4f x = simd4f_create(1, 2, 3, 4);

        should_be_close_to( simd4f_getX(x), 1, epsilon);
        should_be_close_to( simd4f_getY(x), 2, epsilon);
        should_be_close_to( simd4f_getZ(x), 3, epsilon);
        should_be_close_to( simd4f_getW(x), 4, epsilon);

        // octave simd4f: [1,2,3,4]
        should_be_equal_simd4f(x, simd4f_create(1.000000, 2.000000, 3.000000, 4.000000), epsilon );
        
    }
    
    
}
#ifdef _MSC_VER
#include <malloc.h>
#else
#include <alloca.h>
#endif

#define unaligned_mem(n) ((float*)((unsigned char*)alloca(sizeof(float)*n+1)+1))

describe(simd4f, "utilities") {

    it("should have simd4f_uload4 for loading four float values from an unaligned float array into simd4f") {
        float *f = unaligned_mem(4);
        f[0] = 1;
        f[1] = 2;
        f[2] = 3;
        f[3] = 4;
        simd4f x = simd4f_uload4(f);
        // octave simd4f: [1,2,3,4]
        should_be_equal_simd4f(x, simd4f_create(1.000000, 2.000000, 3.000000, 4.000000), epsilon );
    }

    it("should have simd4f_uload3 for loading three float values from an unaligned float array into simd4f") {
        float *f = unaligned_mem(3);
        f[0] = 1;
        f[1] = 2;
        f[2] = 3;
        simd4f x = simd4f_uload3(f);
        // octave simd4f: [1,2,3]
        should_be_equal_simd4f(x, simd4f_create(1.000000, 2.000000, 3.000000, 0), epsilon );
    }

    it("should have simd4f_uload2 for loading two float values from float an unaligned array into simd4f") {
        float *f = unaligned_mem(2);
        f[0] = 1;
        f[1] = 2;
        simd4f x = simd4f_uload2(f);
        // octave simd4f: [1,2]
        should_be_equal_simd4f(x, simd4f_create(1.000000, 2.000000, 0, 0), epsilon );
    }


    it("should have simd4f_ustore4 for storing four float values from simd4f to an unaligned array") {
        float *f = unaligned_mem(4);
        f[0] = -1;
        f[1] = -1;
        f[2] = -1;
        f[3] = -1;
        simd4f a = simd4f_create(1,2,3,4);
        simd4f_ustore4(a, f);
        should_be_close_to(f[0], 1, epsilon);
        should_be_close_to(f[1], 2, epsilon);
        should_be_close_to(f[2], 3, epsilon);
        should_be_close_to(f[3], 4, epsilon);
    }

    it("should have simd4f_ustore3 for storing three float values from simd4f to an unaligned array") {
        float *f = unaligned_mem(3);
        f[0] = -1;
        f[1] = -1;
        f[2] = -1;
        simd4f a = simd4f_create(1,2,3,4);
        simd4f_ustore3(a, f);
        should_be_close_to(f[0], 1, epsilon);
        should_be_close_to(f[1], 2, epsilon);
        should_be_close_to(f[2], 3, epsilon);
    }

    it("should have simd4f_ustore2 for storing two float values from simd4f to an unaligned array") {
        float *f = unaligned_mem(2);
        f[0] = -1;
        f[1] = -1;
        simd4f a = simd4f_create(1,2,3,4);
        simd4f_ustore2(a, f);
        should_be_close_to(f[0], 1, epsilon);
        should_be_close_to(f[1], 2, epsilon);
    }




    it("should have simd4f_splat that expands a single scalar to all elements") {
        simd4f x = simd4f_splat(42);
        // octave simd4f: [42,42,42,42]
        should_be_equal_simd4f(x, simd4f_create(42.000000, 42.000000, 42.000000, 42.000000), epsilon );
    }

    it("should have simd4f_splat_x,y,z,w splatting of an element") {
        simd4f a = simd4f_create(1,2,3,4);

        simd4f x;
        
        x = simd4f_splat_x(a);
        // octave simd4f: [1,1,1,1]
        should_be_equal_simd4f(x, simd4f_create(1.000000, 1.000000, 1.000000, 1.000000), epsilon );

        x = simd4f_splat_y(a);
        // octave simd4f: [2,2,2,2]
        should_be_equal_simd4f(x, simd4f_create(2.000000, 2.000000, 2.000000, 2.000000), epsilon );

        x = simd4f_splat_z(a);
        // octave simd4f: [3,3,3,3]
        should_be_equal_simd4f(x, simd4f_create(3.000000, 3.000000, 3.000000, 3.000000), epsilon );

        x = simd4f_splat_w(a);
        // octave simd4f: [4,4,4,4]
        should_be_equal_simd4f(x, simd4f_create(4.000000, 4.000000, 4.000000, 4.000000), epsilon );
    }
    
    it("should have simd4f_sum that adds elements") {
        simd4f a = simd4f_create(1,2,3,4);
        simd4f x = simd4f_sum(a);
        // octave simd4f: [sum([1,2,3,4]), sum([1,2,3,4]), sum([1,2,3,4]), sum([1,2,3,4])]
        should_be_equal_simd4f(x, simd4f_create(10.000000, 10.000000, 10.000000, 10.000000), epsilon );
        
    }
        
    it("should have simd4f_reciprocal") {
        simd4f a = simd4f_create(1.0f,2,3,9999);
        simd4f x = simd4f_reciprocal(a);
        const float epsilon = 0.001f;
        // octave simd4f: 1 ./ [1,2,3,9999]
        should_be_equal_simd4f(x, simd4f_create(1.000000, 0.500000, 0.333333, 0.000100), epsilon );
    }

    it("should have simd4f_sqrt") {
        simd4f a = simd4f_create(1.0f,2,3,9999);
        simd4f x = simd4f_sqrt(a);
        const float epsilon = 0.001f;
        // octave simd4f:  sqrt([1,2,3,9999])
        should_be_equal_simd4f(x, simd4f_create(1.000000, 1.414214, 1.732051, 99.995000), epsilon );
    }

    it("should have simd4f_rsqrt for reciprocal of square-root") {
        simd4f a = simd4f_create(1.0f,2,3,9999);
        simd4f x = simd4f_rsqrt(a);
        const float epsilon = 0.001f;
        // octave simd4f:  1 ./ sqrt([1,2,3,9999])
        should_be_equal_simd4f(x, simd4f_create(1.000000, 0.707107, 0.577350, 0.010001), epsilon );
    }

}

describe(simd4f, "arithmetic with another simd4f") {

    it("should have simd4f_add for component-wise addition") {
        simd4f a = simd4f_create(1,2,3,4);
        simd4f b = simd4f_create(10,20,30,40);
        
        simd4f x = simd4f_add(a,b);
        // octave simd4f: [1,2,3,4] + [10,20,30,40]
        should_be_equal_simd4f(x, simd4f_create(11.000000, 22.000000, 33.000000, 44.000000), epsilon );
    }

    it("should have simd4f_sub for component-wise subtraction") {
        simd4f a = simd4f_create(1,2,3,4);
        simd4f b = simd4f_create(10,20,30,40);
        
        simd4f x = simd4f_sub(b,a);
        // octave simd4f: [10,20,30,40] - [1,2,3,4] 
        should_be_equal_simd4f(x, simd4f_create(9.000000, 18.000000, 27.000000, 36.000000), epsilon );
    }

    it("should have simd4f_mul for component-wise multiply") {
        simd4f a = simd4f_create(1,2,3,4);
        simd4f b = simd4f_create(10,20,30,40);
        
        simd4f x = simd4f_mul(a,b);
        // octave simd4f: [1,2,3,4] .* [10,20,30,40]
        should_be_equal_simd4f(x, simd4f_create(10.000000, 40.000000, 90.000000, 160.000000), epsilon );
    }

    it("should have simd4f_div for component-wise division") {
        simd4f a = simd4f_create(1,2,3,4);
        simd4f b = simd4f_create(10,20,30,40);
        
        simd4f x = simd4f_div(b,a);
        // octave simd4f: [10,20,30,40] ./ [1,2,3,4] 
        should_be_equal_simd4f(x, simd4f_create(10.000000, 10.000000, 10.000000, 10.000000), epsilon );
    }

}


describe(simd4f, "vector math") {
    
    it("should have simd4f_dot4 for four component dot product") {
        simd4f a = simd4f_create(1,2,3,4);
        simd4f b = simd4f_create(10,20,30,40);
        
        simd4f x = simd4f_dot4(a,b);
        // octave simd4f: [dot([1, 2, 3, 4], [10, 20, 30, 40]),dot([1, 2, 3, 4], [10, 20, 30, 40]),dot([1, 2, 3, 4], [10, 20, 30, 40]),dot([1, 2, 3, 4], [10, 20, 30, 40])]
        should_be_equal_simd4f(x, simd4f_create(300.000000, 300.000000, 300.000000, 300.000000), epsilon );
    }

    it("should have simd4f_dot3 for three component dot product") {
        simd4f a = simd4f_create(1,2,3,9999);
        simd4f b = simd4f_create(10,20,30,-9990);
        
        simd4f x = simd4f_dot3(a,b);
        // octave simd4f: [dot([1, 2, 3], [10, 20, 30]),dot([1, 2, 3], [10, 20, 30]),dot([1, 2, 3], [10, 20, 30]),dot([1, 2, 3], [10, 20, 30])]
        should_be_equal_simd4f(x, simd4f_create(140.000000, 140.000000, 140.000000, 140.000000), epsilon );
    }

    it("should have simd4f_dot2 for two component dot product") {
        simd4f a = simd4f_create(1,2,3,9999);
        simd4f b = simd4f_create(10,20,30,-9990);
        
        simd4f x = simd4f_dot2(a,b);
        // octave simd4f: [dot([1, 2], [10, 20]),dot([1, 2], [10, 20]),dot([1, 2], [10, 20]),dot([1, 2], [10, 20])]
        should_be_equal_simd4f(x, simd4f_create(50.000000, 50.000000, 50.000000, 50.000000), epsilon );
    }
    
    it("should have simd4f_length4 for four component vector length") {
        simd4f a = simd4f_create(1,2,-3,9999);
        simd4f x = simd4f_length4(a);
        // octave simd4f: [norm([1,2,-3,9999]), norm([1,2,-3,9999]), norm([1,2,-3,9999]), norm([1,2,-3,9999])]
        should_be_equal_simd4f(x, simd4f_create(9999.000700, 9999.000700, 9999.000700, 9999.000700), epsilon );

    }

    it("should have simd4f_length3 for three component vector length") {
        simd4f a = simd4f_create(1,2,-3,9999);
        simd4f x = simd4f_length3(a);
        // octave simd4f: [norm([1,2,-3]), norm([1,2,-3]), norm([1,2,-3]), norm([1,2,-3])]
        should_be_equal_simd4f(x, simd4f_create(3.741657, 3.741657, 3.741657, 3.741657), epsilon );

    }

    it("should have simd4f_length2 for two component vector length") {
        simd4f a = simd4f_create(1,2,-3,9999);
        simd4f x = simd4f_length2(a);
        // octave simd4f: [norm([1,2]),norm([1,2]),norm([1,2]),norm([1,2])]
        should_be_equal_simd4f(x, simd4f_create(2.236068, 2.236068, 2.236068, 2.236068), epsilon );

    }


    it("should have simd4f_length4_squared for four component squared vector length") {
        simd4f a = simd4f_create(1,2,-3,9999);
        simd4f x = simd4f_length4_squared(a);
        // octave simd4f: ([(dot([1,2,-3,9999], [1,2,-3,9999])), (dot([1,2,-3,9999], [1,2,-3,9999])), (dot([1,2,-3,9999], [1,2,-3,9999])), (dot([1,2,-3,9999], [1,2,-3,9999]))])
        should_be_equal_simd4f(x, simd4f_create(99980015.000000, 99980015.000000, 99980015.000000, 99980015.000000), epsilon );

    }

    it("should have simd4f_length3_squared for three component squared vector length") {
        simd4f a = simd4f_create(1,2,-3,9999);
        simd4f x = simd4f_length3_squared(a);
        // octave simd4f: ([dot([1,2,-3], [1,2,-3]), dot([1,2,-3], [1,2,-3]), dot([1,2,-3], [1,2,-3]), dot([1,2,-3], [1,2,-3])])
        should_be_equal_simd4f(x, simd4f_create(14.000000, 14.000000, 14.000000, 14.000000), epsilon );

    }

    it("should have simd4f_length2_squared for two component squared vector length") {
        simd4f a = simd4f_create(1,2,-3,9999);
        simd4f x = simd4f_length2_squared(a);
        // octave simd4f: ([dot([1,2], [1,2]), dot([1,2], [1,2]), dot([1,2], [1,2]), dot([1,2], [1,2])])
        should_be_equal_simd4f(x, simd4f_create(5.000000, 5.000000, 5.000000, 5.000000), epsilon );

    }
    
    
    
    it("should have simd4f_cross3 for cross product") {
        simd4f a = simd4f_create(1,12,3,-9999);
        simd4f b = simd4f_create(5,6,-17, 9999);

        simd4f x = simd4f_cross3(a,b);
        // octave simd4f: horzcat(  cross( [1,12,3], [5,6,-17] )  , [0] )
        should_be_equal_simd4f(x, simd4f_create(-222.000000, 32.000000, -54.000000, 0.000000), epsilon );

    }
    
    it("should have simd4f_normalize4 for normalizing four const vector to unit length") {
        simd4f a = simd4f_create(1,2,3,4);
        simd4f x = simd4f_normalize4(a);
        const float epsilon = 0.001f;
        // octave simd4f: [1,2,3,4] / norm([1,2,3,4])
        should_be_equal_simd4f(x, simd4f_create(0.182574, 0.365148, 0.547723, 0.730297), epsilon );
    }

    it("should have simd4f_normalize3 for normalizing three component vector to unit length") {
        simd4f a = simd4f_create(1,2,3,0);
        simd4f x = simd4f_normalize4(a);
        const float epsilon = 0.001f;
        // octave simd4f: [1,2,3,0] / norm([1,2,3])
        should_be_equal_simd4f(x, simd4f_create(0.267261, 0.534522, 0.801784, 0.000000), epsilon );
    }

    it("should have simd4f_normalize2 for normalizing two component vector to unit length") {
        simd4f a = simd4f_create(1,2,0,0);
        simd4f x = simd4f_normalize4(a);
        const float epsilon = 0.001f;
        // octave simd4f: [1,2,0,0] / norm([1,2])
        should_be_equal_simd4f(x, simd4f_create(0.447214, 0.894427, 0.000000, 0.000000), epsilon );
    }

    
}


