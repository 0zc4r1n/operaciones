from conans import ConanFile, AutoToolsBuildEnvironment
from conans import tools

class TestOperaciones(ConanFile):
    name = "operaciones"
    version = "0.1.2"
    settings = "os", "compiler", "build_type", "arch"
    generators = "make"
    exports_sources = "src/*"
    reference = "operaciones/0.1.2@uxpos/testing"
    license = "Sodimac UXPOS 1.0"
    url = "https://github.com/0zc4r1n/operaciones"
    description = "Libreria para operaciones basicas matematicas"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    requires = "operaciones/0.1.2@uxpos/stable"

    def build(self):
        with tools.chdir("src"):
            atools = AutoToolsBuildEnvironment(self)
            atools.make()

    def package(self):
        self.copy("*test", dst="bin", keep_path=False)

    def deploy(self):
        self.copy("*", src="bin", dst="bin")

