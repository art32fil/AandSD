    import unittest
    import subprocess


    class Tester(unittest.TestCase):

        def test1(self):
            print("d")
            print("a")
            self.assertIn("Finished right", subprocess.check_output(["./a.out", "d", "a"], universal_newlines=True))

        def test2(self):
            print("d")
            print("w")
            self.assertIn("Finished right", subprocess.check_output(["./a.out", "d", "w"], universal_newlines=True))

        def test3(self):
            print("i")
            print("a")
            self.assertIn("Finished right", subprocess.check_output(["./a.out", "i", "a"], universal_newlines=True))

        def test4(self):
            print("i")
            print("w")
            self.assertIn("Finished right", subprocess.check_output(["./a.out", "i", "w"], universal_newlines=True))


    if __name__ == '__main__':
        unittest.main()

