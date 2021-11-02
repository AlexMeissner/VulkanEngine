#include <Windows.h>

class vulkan_application
{
public:
    void run()
    {
        initialize();
        loop();
        cleanup();
    }

private:
    void initialize()
    {

    }

    void loop()
    {

    }

    void cleanup()
    {

    }
};

int main()
{
    vulkan_application app;
    app.run();

    return EXIT_SUCCESS;
}