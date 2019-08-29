Glew : http://glew.sourceforge.net/
Dl fichiers binaires, dézipper, placer le dossier à un endroit pratique
FreeGlut : https://www.transmissionzero.co.uk/files/software/development/GLUT/freeglut-MSVC.zip
Dézipper, placer à un endroit pratique

Dans visual :
Ouvrir le projet cloné
Projet -> Propriétés de Moteur_physique
C/C++ -> Général -> Autres répertoires Include -> <Modifier> -> Ajouter les répertoires include pour freeglut et glew
exemple : D:\Programmes\freeglut\include;D:\Programmes\GLEW-2.1.0\glew-2.1.0\include
Editeur de liens -> Général -> Répertoires de bibliothèques supplémentaires -> <Modifier> -> Ajouter les répertoires qui contiennent les .lib pour freeglut et glew
exemple : D:\Programmes\freeglut\lib\x64;D:\Programmes\GLEW-2.1.0\glew-2.1.0\lib\Release\x64
Editeur de liens -> entrée -> Dépendances supplémentaires -> <Modifier> -> Ajouter glew32.lib freeglut.lib opengl32.lib

Si ça indique quand vous executez (Ctrl+F5) qu'il manque des dll, copiez freeglut.dll et glew.dll à côté de l'exécutable dans le dossier Debug
Les dll sont dans le dossier bin ou lib des dossiers dézippés.

Enjoy :)