Glew : http://glew.sourceforge.net/
Dl fichiers binaires, d�zipper, placer le dossier � un endroit pratique
FreeGlut : https://www.transmissionzero.co.uk/files/software/development/GLUT/freeglut-MSVC.zip
D�zipper, placer � un endroit pratique

Dans visual :
Ouvrir le projet clon�
Projet -> Propri�t�s de Moteur_physique
C/C++ -> G�n�ral -> Autres r�pertoires Include -> <Modifier> -> Ajouter les r�pertoires include pour freeglut et glew
exemple : D:\Programmes\freeglut\include;D:\Programmes\GLEW-2.1.0\glew-2.1.0\include
Editeur de liens -> G�n�ral -> R�pertoires de biblioth�ques suppl�mentaires -> <Modifier> -> Ajouter les r�pertoires qui contiennent les .lib pour freeglut et glew
exemple : D:\Programmes\freeglut\lib\x64;D:\Programmes\GLEW-2.1.0\glew-2.1.0\lib\Release\x64
Editeur de liens -> entr�e -> D�pendances suppl�mentaires -> <Modifier> -> Ajouter glew32.lib freeglut.lib opengl32.lib

Si �a indique quand vous executez (Ctrl+F5) qu'il manque des dll, copiez freeglut.dll et glew.dll � c�t� de l'ex�cutable dans le dossier Debug
Les dll sont dans le dossier bin ou lib des dossiers d�zipp�s.

Enjoy :)