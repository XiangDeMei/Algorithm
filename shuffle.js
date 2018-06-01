function shuffle(array) {
  const pokers = array;
  for (let index = pokers.length - 1; index > 0; index--) {
    const pos = Math.round(Math.random() * index);
    [pokers[pos], pokers[index]] = [pokers[index], pokers[pos]];
  }
  return pokers;
}
