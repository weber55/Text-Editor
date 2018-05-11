#ifndef TEXTFILE_H
#define TEXTFILE_H

class Textfile {

  const char *filename;
  int numLines;

 public:
  Textfile(const char *filename);

  /**
   * Checks if a file with the given name is accessible.
   * @param *filename Name of file to check
   * @return True if file is accessible, false if not.
   */
  bool isAvailable();

  void setNumLines();

  void save();

  void saveAs();

  int getNumLines();
  const char *getFilename();
};

#endif


