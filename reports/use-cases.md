# Use Cases

Casos de Utilização
-------------------

Se a perspetiva se cumprir, a aplicação final conseguirá, na sua camada superior, receber os pedidos dos utilizadores e, na camada inferior, proceder à sua gestão e delineação da respetiva rota, a percorrer pelos estafetas responsáveis por atender os pedidos. O objetivo será sempre, na generalidade das situações, escolher o caminho mais curto entre a localização inicial do estafeta, o restaurante e, por fim, a morada do cliente.

Como idealização dos casos de utilização, prevê-se, no final da implementação, a existência de vários mapas, de várias cidades, cada uma com um conjunto de estafetas a operar e um conjunto de restaurantes já registados. O utilizador terá, simplesmente, de identificar a cidade e proceder com a encomenda, escolhendo a sua localização, o restaurante e elaborando, por fim, o seu pedido. O sistema atribuir-lhe-á um estafeta livre e com capacidade para o transportar, calculando as distâncias mínimas e estabelecendo o percurso. Esta informação, nomeadamente, o estafeta responsável e a rota a percorrer, irá ser retornada, como resultado. 

Para que a aplicação garanta alguma interação, ao nível do utilizador, haverá uma interface simples que permitirá o registo de novos pedidos, estafetas, ou restaurantes. 

Como última nota, será ponderado o uso, ou implementação, de uma API de visualização de grafos, como auxílio à compreensão e perceção das várias circunstâncias e consequências dos algoritmos abordados. O percurso final do estafeta poderá ser apresentado num mapa real, para que o utilizador possa ter a noção da utilização e capacidade do nosso sistema na gestão das rotas e cálculo efetivo das distâncias mínimas.