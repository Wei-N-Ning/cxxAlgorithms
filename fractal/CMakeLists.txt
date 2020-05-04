add_executable(fractal_mandelbrot mandelbrot.cpp)
target_link_libraries(fractal_mandelbrot PRIVATE doctest)
add_test(NAME "fractal::mandelbrot" COMMAND fractal_mandelbrot)
