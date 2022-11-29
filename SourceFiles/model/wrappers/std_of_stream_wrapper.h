#ifndef SOURCEFILES_MODEL_WRAPPERS_STD_OF_STREAM_WRAPPER_H_
#define SOURCEFILES_MODEL_WRAPPERS_STD_OF_STREAM_WRAPPER_H_

#include <filesystem>
#include <fstream>

namespace CommunalCalculator::Wrappers {

class STDOfStreamWrapper : public std::ofstream {
 public:
  virtual void Open(const std::filesystem::path &filename,
                    std::ios_base::openmode mode);

  virtual void Close();

  virtual auto IsOpen() -> bool;

  virtual auto Write(const char_type *data, std::streamsize count)
      -> basic_ostream &;
};

}  // namespace CommunalCalculator::Wrappers

#endif  // SOURCEFILES_MODEL_WRAPPERS_STD_OF_STREAM_WRAPPER_H_
