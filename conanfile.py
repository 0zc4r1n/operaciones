from conans import ConanFile, AutoToolsBuildEnvironment
from conans import tools

class Promociones(ConanFile):
    name = "operaciones"
    version = "0.1.1"
    settings = "os", "compiler", "build_type", "arch"
    generators = "make"
    exports_sources = "src/*"
#    requires = "expat/2.2.7"

    def build(self):
        with tools.chdir("src"):
            atools = AutoToolsBuildEnvironment(self)
            # atools.configure() # use it to run "./configure" if using autotools
            atools.make()

    def package(self):
        self.copy("*.h", dst="include", src="src")
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["promociones"]
