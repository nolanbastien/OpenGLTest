# Mincraft Clone

J'ai écrit ce code en lisant le livre _learn opengl graphics programming_ (https://learnopengl.com/book/book_pdf.pdf) et en suivant les tutoriels OpenGL de la chaîne youtube The Cherno dans le but de me familiariser avec des concepts de programmation graphique.

J'ai décidé de transformer ce projet en clone de minecraft. C'est pourquoi j'ai inclus un système pour se déplacer dans le monde et pourquoi je _render_ des blocs. D'autres features s'en viennent.

### Le projet inclut:

- Gestion des Vertex Buffer Array
- Rendering par index
- Utilisation de textures
- WASD et souris pour bouger et regarder autour

### À implémenter:

- Rendering qui s'assure de ne pas render les formes hors du champ de vision
- Système pour render les blocks par "chunk" de 64x64x64
- Système pour détruire et construire des blocs
- Système de lumière

### Screenshot:

Une fois compilé, le projet ressemble à ceci:

![image](https://github.com/nolanbastien/OpenGLTest/assets/80637967/c2045ba9-3236-49b9-a3df-3ab77c25c568)

L'interface IMGUI applique des transformations au cube.
