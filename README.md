## Philosophers

https://fr.wikipedia.org/wiki/D%C3%AEner_des_philosophes

### TODO:

- philo_three
- more tests
- norminette 


### philo_one : threads et mutex

Mutex Synchronisation :
https://youtu.be/GXXE42bkqQk

Mutex man :
https://linux.die.net/man/3/pthread_mutex_init


### philo_two : threads et semaphores


Si on fait un CTRL-C durant l'éxecution du programme, les instructions de fin
ne sont pas executées. L'une des instructions de fin est la destruction du
sémaphore. Comme il n'est pas détruit, il est réouvert à la prochaine execution.

C'est pourquoi le résultat est faussé, la valeur du semaphore est la même
qu'au moment du CTRL-C précédent, donc elle est fausse.

Pour supprimer le semaphore facilement, lancer le programme avec 0 philosophes.

Semaphores with Threads:
https://mtodorovic.developpez.com/linux/programmation-avancee/?page=page_4#L4-4-5

Stop the waiting :
https://stackoverflow.com/questions/47317048/how-to-exit-from-thread-which-is-suspended-by-semaphore

### philo_three : processus et semaphores

Semaphores with Process :
https://www.blaess.fr/christophe/2011/10/09/efficacite-des-ipc-semaphore-et-memoire-partagee/
