module;

export module stb_image;
import std;
namespace stb_image {
  class Image {
  public:
    Image(const std::string &file_path);
    ~Image();
  private:
    char* data = nullptr;
    int width = -1;
    int height = -1;
    int channels = -1;
  };
}